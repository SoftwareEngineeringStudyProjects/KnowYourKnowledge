import * as fs from "fs";
import * as path from "path";
import * as os from "os";
import { FileJsonStorage } from '../../../know-your-knowledge-core/storage/FileJsonStorage' ;
import { KnowledgeItem } from '../../../know-your-knowledge-core/domain/entities/KnowledgeItem';

// SaveResult types
type SaveResultOk = { result: "ok"; fullPath: string };
type SaveResultError = { result: "error"; message: string };
type SaveResult = SaveResultOk | SaveResultError;

describe("FileJsonStorage Integration Tests", () => {
  let storage: FileJsonStorage;
  let tempDir: string;

  beforeAll(() => {
    // Create a temporary directory
    tempDir = fs.mkdtempSync(path.join(os.tmpdir(), "filestorage-"));

  });

  beforeEach(() => {
    // Clean up tempDir before each test
    if (fs.existsSync(tempDir)) {
      for (const file of fs.readdirSync(tempDir)) {
        fs.unlinkSync(path.join(tempDir, file));
      }
    }

    // Create a new storage instance
    storage = new FileJsonStorage({ storageDirectory: tempDir });
  });

  afterAll(() => {
    // Remove tempDir after all tests
    fs.rmSync(tempDir, { recursive: true, force: true });
  });

  // ---------- SAVE & LOAD INTEGRATION ----------
  it("should save and load a string KnowledgeItem", async () => {
    const item: KnowledgeItem = "Hello Integration";
    const where: KnowledgeItem = "string.json";

    const result = (await storage.save(item, where)) as SaveResultOk;
    expect(result.result).toBe("ok");

    const filePath = path.join(tempDir, "string.json");
    expect(fs.existsSync(filePath)).toBe(true);

    const data = await fs.promises.readFile(filePath, "utf-8");
    expect(data).toBe(JSON.stringify(item, null, 2));

    const loaded = await storage.load(where);
    expect(loaded).toBe(item);
  });

  it("should save and load an object KnowledgeItem", async () => {
    const item: KnowledgeItem = { name: "Alice", age: 30 };
    const where: KnowledgeItem = "person.json";

    const result = (await storage.save(item, where)) as SaveResultOk;
    expect(result.result).toBe("ok");

    const filePath = path.join(tempDir, "person.json");
    const data = await fs.promises.readFile(filePath, "utf-8");
    expect(JSON.parse(data)).toEqual(item);

    const loaded = await storage.load(where);
    expect(loaded).toEqual(item);
  });

  it("should save and load an array KnowledgeItem", async () => {
    const item: KnowledgeItem = [
      { id: 1, title: "Note 1" },
      { id: 2, title: "Note 2" },
    ];
    const where: KnowledgeItem = "notes.json";

    const result = (await storage.save(item, where)) as SaveResultOk;
    expect(result.result).toBe("ok");

    const filePath = path.join(tempDir, "notes.json");
    const data = await fs.promises.readFile(filePath, "utf-8");
    expect(JSON.parse(data)).toEqual(item);

    const loaded = await storage.load(where);
    expect(loaded).toEqual(item);
  });

  // ---------- EDGE CASES ----------
  it("should return null when loading a non-existing file", async () => {
    const where: KnowledgeItem = "missing.json";
    const loaded = await storage.load(where);
    expect(loaded).toBeNull();
  });

  it("should return an error when saving with non-string 'where'", async () => {
    const item: KnowledgeItem = "test";
    const where: KnowledgeItem = { invalid: true };

    const result = (await storage.save(item, where)) as SaveResultError;
    expect(result.result).toBe("error");
  });
});
