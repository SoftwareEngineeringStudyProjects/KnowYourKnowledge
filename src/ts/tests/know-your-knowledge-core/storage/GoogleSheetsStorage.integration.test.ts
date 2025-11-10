import { GoogleSheetsStorage } from "../../../know-your-knowledge-core/storage//GoogleSheetsStorage"; // adjust the path
import { authorize } from "../../../know-your-knowledge-core/auth/GoogleSheetsAuth"; // adjust the path
import { OAuth2Client } from "google-auth-library";

describe("GoogleSheetsStorage.load (integration)", () => {
  let storage: GoogleSheetsStorage;
  const SPREADSHEET_ID = "1RR-fsd_zxyqNLDM8mj9gsQpQUtQNLcdHEVxJ9czdAOk"; //process.env.TEST_SPREADSHEET_ID; // set in env or .env

  beforeAll(async () => {
    if (!SPREADSHEET_ID) {
      throw new Error("Missing TEST_SPREADSHEET_ID environment variable.");
    }

    // 🔐 Authenticate using OAuth2 helper (interactive or saved token)
    const auth = await authorize();
    storage = new GoogleSheetsStorage(auth as OAuth2Client);
  });

  it("should load the 'list' sheet with the expected data", async () => {
    const result = await storage.load(SPREADSHEET_ID);
    expect(result).not.toBeNull();

    const list = (result as Record<string, string[][]>)["list"];
    expect(list).toBeDefined();

    const expected = [
      ["Num", "Student"],
      ["1", "Alice Smith"],
      ["2", "Bob Cook"],
      ["3", "Conrad Doe"],
    ];

    expect(list).toEqual(expected);
  }, 30000); // 30s timeout for API roundtrip
});
