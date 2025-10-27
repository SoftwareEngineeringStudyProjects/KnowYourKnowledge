import * as fs from 'fs';
import * as path from 'path';
import { config } from '../config';
import { Storage } from '../domain/entities/Storage';
import { KnowledgeItem } from '../domain/entities/KnowledgeItem';

export class FileJsonStorage extends Storage {
  private storageDir: string;

  constructor() {
    super();
    this.storageDir = config.storageDirectory;

    // Ensure the directory exists
    if (!fs.existsSync(this.storageDir)) {
      fs.mkdirSync(this.storageDir, { recursive: true });
    }
  }

  // Save method accepts and returns KnowledgeItem
  async save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem> {
    // Check if 'where' is a string
    if (typeof where !== 'string') {
      return {
        result: "error",
        message: "The 'where' parameter must be a string"
      };
    }

    const filePath = path.join(this.storageDir, where); // for automatically added extension, replace with `${where}.json`

    try {

      // Save the item to the file
      await fs.promises.writeFile(filePath, JSON.stringify(item, null, 2));
      
      return {
        result: "ok",
        fullPath: filePath
      };
    } catch (error: unknown) {
      // Error handling block: Narrow the 'unknown' type
      console.error('Error saving the file:', error);
      if (error instanceof Error) {
        return { result: 'error', message: error.message };
      }
      return { result: 'error', message: 'An unknown error occurred' };
    }
  }

  // Load method accepts 'where' as string, returns a string or null
  async load(where: KnowledgeItem): Promise<KnowledgeItem | null> {

    try {
      // Check if 'where' is a string
      if (typeof where !== 'string') {
        throw new Error("The 'where' parameter must be a string");
      }

      const filePath = path.join(this.storageDir, where); // for automatically added extension, replace with `${where}.json`

  
      if (fs.existsSync(filePath)) {
        const fileContent = await fs.promises.readFile(filePath, 'utf-8');
        const item = JSON.parse(fileContent);
        return item; 
      } else {
        return null;
      }
    } catch (error) {
      console.error('Error loading the file:', error);
      return null;
    }
  }
}
