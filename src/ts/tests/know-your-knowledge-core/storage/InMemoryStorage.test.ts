import { InMemoryStorage } from '../../../know-your-knowledge-core/storage/InMemoryStorage' ;
import { KnowledgeItem } from '../../../know-your-knowledge-core/domain/entities/KnowledgeItem';

describe('InMemoryStorage', () => {
  let storage: InMemoryStorage;

  beforeEach(() => {
    storage = new InMemoryStorage();
  });

  describe('save method', () => {
    it('should store an item when "where" is a string', async () => {
      const item: KnowledgeItem = { title: 'Test Knowledge', content: 'Some content' };
      const result = await storage.save(item, 'item_key');
      
      expect(result).toEqual({ result: 'ok' });
      const loadedItem = await storage.load('item_key');
      expect(loadedItem).toEqual(item);
    });

    it('should store an item when "where" is an object with a "key" property', async () => {
      const item: KnowledgeItem = { title: 'Test Knowledge', content: 'Some content' };
      const result = await storage.save(item, { key: 'item_key' });
      
      expect(result).toEqual({ result: 'ok' });
      const loadedItem = await storage.load({ key: 'item_key' });
      expect(loadedItem).toEqual(item);
    });

    it('should store an item in multiple places when "where" is an array of objects with "key" properties', async () => {
      const item: KnowledgeItem = { title: 'Test Knowledge', content: 'Some content' };
      const result = await storage.save(item, [{ key: 'item_key_1' }, { key: 'item_key_2' }]);

      expect(result).toEqual({ result: 'ok' });

      const loadedItem1 = await storage.load({ key: 'item_key_1' });
      expect(loadedItem1).toEqual(item);

      const loadedItem2 = await storage.load({ key: 'item_key_2' });
      expect(loadedItem2).toEqual(item);
    });

    it('should store an item in multiple places when "where" is an array of KnowledgeItems of different types', async () => {
      const item: KnowledgeItem = { title: 'Test Knowledge', content: 'Some content' };
      const result = await storage.save(item, [{ key: 'item_key_1' }, 'item_key_2' ]);

      expect(result).toEqual({ result: 'ok' });

      const loadedItem1 = await storage.load({ key: 'item_key_1' });
      expect(loadedItem1).toEqual(item);

      const loadedItem2 = await storage.load('item_key_2');
      expect(loadedItem2).toEqual(item);
    });

    it('should store an item in multiple places when "where" is an array of KnowledgeItems of different types, including nested arrays', async () => {
      const item: KnowledgeItem = { title: 'Test Knowledge', content: 'Some content' };
      const result = await storage.save(item, [{ key: 'item_key_1' }, [ 'item_key_2', { key: 'item_key_3' }] ]);

      expect(result).toEqual({ result: 'ok' });

      const loadedItem1 = await storage.load({ key: 'item_key_1' });
      expect(loadedItem1).toEqual(item);

      const loadedItem2 = await storage.load('item_key_2');
      expect(loadedItem2).toEqual(item);

      const loadedItem3 = await storage.load({ key: 'item_key_3' });
      expect(loadedItem2).toEqual(item);      
    });    


    it('should return error if "where" is not a string, object with "key", or array', async () => {
      const item: KnowledgeItem = { title: 'Test Knowledge', content: 'Some content' };
      
      // Invalid where parameter: number
      const result1 = await storage.save(item, 123 as any);
      expect(result1).toEqual({ result: 'error', message: 'The "where" parameter must be a string, object with "key", or an array.' });
      
      // Invalid where parameter: null
      const result2 = await storage.save(item, null as any);
      expect(result2).toEqual({ result: 'error', message: 'The "where" parameter must be a string, object with "key", or an array.' });

      // Invalid where parameter: empty object without "key"
      const result3 = await storage.save(item, {});
      expect(result3).toEqual({ result: 'error', message: 'The "where" parameter must be a string, object with "key", or an array.' });
    });

    // it('should return error if "where" is an object with an empty "key" property', async () => {
    //   const item: KnowledgeItem = { title: 'Test Knowledge', content: 'Some content' };
    //   const result = await storage.save(item, { key: '' });
    //   expect(result).toEqual({ result: 'error', message: 'The "where" parameter must be a string, object with "key", or an array.' });
    // });


    it('should store all items when "$all" is used as the key', async () => {
      const items = {
        "item1": { key: "item1", title: 'Test Knowledge 1', content: 'Some content 1' },
        "item2": { key: "item2", title: 'Test Knowledge 2', content: 'Some content 2' },
      };

      const result = await storage.save(items, "$all");

      expect(result).toEqual({ result: 'ok' });

      // Check if individual items are saved
      const loadedItem1 = await storage.load('item1');
      expect(loadedItem1).toEqual(items.item1);

      const loadedItem2 = await storage.load('item2');
      expect(loadedItem2).toEqual(items.item2);
    });
  });

  describe('load method', () => {
    it('should return null if item does not exist for the given key (string)', async () => {
      const result = await storage.load('non_existent_key');
      expect(result).toBeNull();
    });

    it('should return null if item does not exist for the given key (object with key)', async () => {
      const result = await storage.load({ key: 'non_existent_key' });
      expect(result).toBeNull();
    });

    it('should return null if item does not exist for any key in the array', async () => {
      const result = await storage.load([{ key: 'non_existent_key_1' }, { key: 'non_existent_key_2' }]);
      expect(result).toBeNull();
    });

    it('should return all items when "$all" is loaded', async () => {
      const item1: KnowledgeItem = { key: "item1", title: 'Test Knowledge 1', content: 'Some content 1' };
      const item2: KnowledgeItem = { key: "item2", title: 'Test Knowledge 2', content: 'Some content 2' };

      // Save individual items using the regular save method
      await storage.save(item1, 'item1');
      await storage.save(item2, 'item2');

      // Load all items using "$all"
      const allItems = await storage.load("$all");

      expect(allItems).toEqual({
        "item1": item1,
        "item2": item2
      });
    });

    it('should return null when loading "$all" and no items have been saved', async () => {
      // Load all items when nothing has been saved
      const allItems = await storage.load("$all");

      expect(allItems).toBeNull();
    });
  });
});
