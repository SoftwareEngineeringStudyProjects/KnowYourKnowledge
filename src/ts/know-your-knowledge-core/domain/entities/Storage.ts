import { KnowledgeItem } from './KnowledgeItem';

export abstract class Storage {
  // The `save` method stores a KnowledgeItem and potentially updates another one.
  abstract save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem>;

  // The `load` method returns a KnowledgeItem based on the `where` condition.
  abstract load(where: KnowledgeItem): Promise<KnowledgeItem | null>;
}
