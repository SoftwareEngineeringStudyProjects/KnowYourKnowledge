import * as fs from "fs";
import * as path from "path";
import { FileJsonStorage } from '../../../know-your-knowledge-core/storage/FileJsonStorage' ;
import { KnowledgeItem } from '../../../know-your-knowledge-core/domain/entities/KnowledgeItem';

// --- Mock fs (handles both fs and fs.promises APIs) ---
jest.mock("fs", () => {
  const actualFs = jest.requireActual("fs");
  return {
    ...actualFs,
    existsSync: jest.fn(),
    mkdirSync: jest.fn(),
    promises: {
      readFile: jest.fn(),
      writeFile: jest.fn(),
      mkdir: jest.fn(),
      access: jest.fn(),
    },
  };
});
const mockedFs = fs as unknown as jest.Mocked<typeof fs>;
const mockedFsPromises = fs.promises as jest.Mocked<typeof fs.promises>;

// --- Mock config module ---
jest.mock('../../../know-your-knowledge-core/config', () => ({
  config: {
    storageDirectory: "/mock/storage",
  },
}));

import { config } from '../../../know-your-knowledge-core/config';

// --- Helper types and generic casting function ---

type SaveResultOk = { result: "ok"; fullPath: string };
type SaveResultError = { result: "error"; message: string };
type SaveResult = SaveResultOk | SaveResultError;

/** Generic cast helper for test assertions */
function asType<T>(value: unknown): T {
  return value as T;
}

// --- Tests ---

describe("FileJsonStorage", () => {
  let storage: FileJsonStorage;

  beforeEach(() => {
    jest.clearAllMocks();
  });

  // ---------- CONSTRUCTOR TESTS ----------
  describe("constructor", () => {
    it("should create storage directory if it does not exist", () => {
      mockedFs.existsSync.mockReturnValue(false);

      storage = new FileJsonStorage();

      expect(mockedFs.existsSync).toHaveBeenCalledWith(config.storageDirectory);
      expect(mockedFs.mkdirSync).toHaveBeenCalledWith(config.storageDirectory, { recursive: true });
    });

    it("should not create directory if it already exists", () => {
      mockedFs.existsSync.mockReturnValue(true);

      storage = new FileJsonStorage();

      expect(mockedFs.existsSync).toHaveBeenCalledWith(config.storageDirectory);
      expect(mockedFs.mkdirSync).not.toHaveBeenCalled();
    });
  });

  // ---------- SAVE TESTS ----------
  describe("save()", () => {
    beforeEach(() => {
      mockedFs.existsSync.mockReturnValue(true);
      storage = new FileJsonStorage();
    });

    it("should save a simple string KnowledgeItem", async () => {
      const item: KnowledgeItem = "Hello world";
      const where: KnowledgeItem = "stringItem.json";

      const result = asType<SaveResultOk>(await storage.save(item, where));

      expect(mockedFs.promises.writeFile).toHaveBeenCalledWith(
        path.join(config.storageDirectory, "stringItem.json"),
        JSON.stringify(item, null, 2)
      ); // no need for encoding parameter - it is "utf8" by default
      expect(result.result).toBe("ok");
      expect(result.fullPath).toBe(path.join(config.storageDirectory, "stringItem.json"));
    });

    it("should return an error result if 'where' is not a string", async () => {
      const item: KnowledgeItem = "test";
      const where: KnowledgeItem = { not: "a string" };

      const result = asType<SaveResultError>(await storage.save(item, where));

      expect(result.result).toBe("error");
      expect(result.message).toBe("The 'where' parameter must be a string");
    });

    it("should return an error result if writing file fails", async () => {
      mockedFsPromises.writeFile.mockRejectedValueOnce(new Error("Disk full"));
      const where: KnowledgeItem = "bad.json";

      const result = asType<SaveResultError>(await storage.save("data", where));

      expect(result.result).toBe("error");
      expect(result.message).toBe("Disk full");
    });
  });

  // ---------- LOAD TESTS ----------
  describe("load()", () => {
    beforeEach(() => {
      mockedFs.existsSync.mockReturnValue(true);
      storage = new FileJsonStorage();
    });

    it("should load and parse a string KnowledgeItem", async () => {
      mockedFsPromises.readFile.mockResolvedValueOnce('"hello world"');
      const where: KnowledgeItem = "string.json";

      const item = await storage.load(where);
      expect(item).toBe("hello world");
    });

    it("should return null if target file does not exist", async () => {
      mockedFs.existsSync.mockReturnValue(false);
      const where: KnowledgeItem = "missing.json";

      const item = await storage.load(where);
      expect(item).toBeNull();
      expect(mockedFs.promises.readFile).not.toHaveBeenCalled();
    });

    it("should return null if 'where' is not a string", async () => {
      const where: KnowledgeItem = { not: "a string" };

      const item = await storage.load(where);
      expect(item).toBeNull();
    });
  });
});
