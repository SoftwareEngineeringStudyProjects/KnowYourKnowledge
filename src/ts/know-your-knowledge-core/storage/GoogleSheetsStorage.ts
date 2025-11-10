import { google, sheets_v4 } from "googleapis";
import {
  OAuth2Client,
  //JWT,
  BaseExternalAccountClient,
  //ExternalAccountAuthorizedUserClient,
} from "google-auth-library";

type GoogleAuthClient =
  | OAuth2Client
  //| JWT
  | BaseExternalAccountClient
  //| ExternalAccountAuthorizedUserClient;


// === Your base interfaces ===
export type KnowledgeItem = Record<string, any> | KnowledgeItem[] | string;

export abstract class Storage {
  abstract save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem>;
  abstract load(where: KnowledgeItem): Promise<KnowledgeItem | null>;
}

// === Google Sheets implementation ===
export class GoogleSheetsStorage extends Storage {
  private sheets: sheets_v4.Sheets;

  constructor(auth: GoogleAuthClient) {
    super();
    this.sheets = google.sheets({ version: "v4", auth });
  }

  async save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem> {
    throw new Error("Not implemented");
  }

  async load(where: KnowledgeItem): Promise<KnowledgeItem | null> {
    if (typeof where !== "string") {
      throw new Error("`where` must be a Google Spreadsheet ID (string)");
    }

    const spreadsheetId = where;

    try {
      // 1️⃣ Get spreadsheet metadata (sheet names)
      const metadataResponse = await this.sheets.spreadsheets.get({
        spreadsheetId,
      });

      const sheetsMeta = metadataResponse.data.sheets;
      if (!sheetsMeta || sheetsMeta.length === 0) {
        return {};
      }

      // 2️⃣ Extract all sheet names
      const sheetNames = sheetsMeta.map(s => s.properties?.title).filter(Boolean) as string[];

      // 3️⃣ Fetch all sheets in a batch request
      const valuesResponse = await this.sheets.spreadsheets.values.batchGet({
        spreadsheetId,
        ranges: sheetNames,
      });

      // 4️⃣ Map results
      const result: Record<string, string[][]> = {};
      (valuesResponse.data.valueRanges || []).forEach((range, i) => {
        const name = sheetNames[i];
        const rows = range.values || [];
        result[name] = rows;
      });

      return result;
    } catch (err: any) {
      console.error("❌ Failed to load Google Sheets data:", err.message);
      return null;
    }
  }
}
