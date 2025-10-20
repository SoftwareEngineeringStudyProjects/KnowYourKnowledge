import { Storage } from '../domain/entities/Storage';
import { KnowledgeItem } from '../domain/entities/KnowledgeItem';

export class InMemoryStorage extends Storage{
  private storage: Map<string, KnowledgeItem> = new Map();

  // Implement the save method: store a KnowledgeItem
  async save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem> {
    try {
      if (typeof where === 'string') {
        // If 'where' is a string, use it as the key where the item will be stored
        this.storage.set(where, item);
      } else if (this.isObject(where) && 'key' in where) {
        // If 'where' is an object and has a 'key' property, use the 'key' value as the storage key
        const key = where.key;
        this.save(item, key);
      } else if (Array.isArray(where)) {
        // If 'where' is an array, call save for each item in the array
        where.forEach((whereItem) => {
          if (this.isObject(whereItem) && 'key' in whereItem) {
            this.save(item, whereItem);
          }
        });
      } else {
        throw new Error('The "where" parameter must be a string, object with "key", or an array.');
      }

      // If we reach here, the save was successful
      return { result: 'ok' };
    } catch (error: unknown) {
      // Error handling block: Narrow the 'unknown' type
      if (error instanceof Error) {
        return { result: 'error', message: error.message };
      }
      return { result: 'error', message: 'An unknown error occurred' };
    }
  }

  // Implement the load method: retrieve a KnowledgeItem by the "where" condition
  async load(where: KnowledgeItem): Promise<KnowledgeItem | null> {
    if (typeof where === 'string') {
      // If 'where' is a string, return the item stored with that key
      return this.storage.get(where) || null;
    } else if (this.isObject(where) && 'key' in where) {
      // If 'where' is an object with a 'key' property, use it to retrieve the item
      const key = where.key;
      return this.storage.get(key) || null;
    } else if (Array.isArray(where)) {
      // If 'where' is an array, return an array of items for each key in the array
      const result: KnowledgeItem[] = [];
      where.forEach((whereItem) => {
        if (this.isObject(whereItem) && 'key' in whereItem) {
          const key = whereItem.key;
          const item = this.storage.get(key);
          if (item) result.push(item);
        }
      });
      return result.length > 0 ? result : null;
    }
    return null;
  }

  // Utility function to check if an item is an object
  private isObject(item: any): item is Record<string, any> {
    return typeof item === 'object' && item !== null && !Array.isArray(item);
  }
}
