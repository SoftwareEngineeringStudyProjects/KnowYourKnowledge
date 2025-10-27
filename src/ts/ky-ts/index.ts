#!/usr/bin/env node
import { getVersion } from "../know-your-knowledge-core";
import { FileJsonStorage } from "../know-your-knowledge-core/storage/FileJsonStorage";
import { KnowledgeItem } from "../know-your-knowledge-core/domain/entities/KnowledgeItem";
import * as path from "path";

// CLI arguments
const args = process.argv.slice(2);

// Initialize storage
const storage = new FileJsonStorage();
const keysFile: KnowledgeItem = "keys.json";

// Helper to load current keys
async function loadKeys(): Promise<Record<string, any>> {
  const data = (await storage.load(keysFile)) as Record<string, any> | null;
  return data || {};
}

// ---------- CLI Commands ----------
async function main() {
  const command = args[0];
  const cliName = 'ky-ts'

  switch (command) {
    case "version":
      console.log(getVersion());
      break;

    case "add-key": {
      const key = args[1];
      const value = args[2];
      if (!key || value === undefined) {
        console.log(`Usage: ${cliName} add-key <key> <value>`);
        return;
      }

      const keys = await loadKeys();
      keys[key] = value;

      const result = await storage.save(keys, keysFile);
      if ((result as any).result === "ok") {
        console.log(`Key '${key}' added successfully.`);
      } else {
        console.error(`Error saving key: ${(result as any).message}`);
      }
      break;
    }

    case "get-key": {
      const key = args[1];
      if (!key) {
        console.log(`Usage: ${cliName} get-key <key>`);
        return;
      }

      const keys = await loadKeys();
      if (keys[key] !== undefined) {
        console.log(keys[key]);
      } else {
        console.log(`Key '${key}' not found.`);
      }
      break;
    }

    default:
      console.log(`Unknown command. Try: ${cliName} version | add-key | get-key`);
  }
}

// Run CLI
main().catch(err => {
  console.error("Unexpected error:", err);
});

