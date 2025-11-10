# Prompt
Provide documentation for the following TypeScript code:

# TypeScript


### `KnowledgeItem` Type Definition

```typescript
export type KnowledgeItem = Record<string, any> | KnowledgeItem[] | string;
```

#### **Description**

The `KnowledgeItem` type is a **recursive union type** that can represent:

1. A **plain object** (`Record<string, any>`) — an object with string keys and values of any type.
2. An **array** of `KnowledgeItem` values (`KnowledgeItem[]`) — allowing for nested or hierarchical data structures.
3. A **string** — allowing simple text-based knowledge items.

This type is useful for representing **flexible, nested knowledge structures**, such as trees, graphs, or documents where each node can be a string, an object, or another list of knowledge items.

#### **Type Components**

* `Record<string, any>`: Represents a generic JavaScript object, e.g. `{ title: "AI", description: "Artificial Intelligence" }`.
* `KnowledgeItem[]`: Represents a recursive structure where a knowledge item may contain a list of other knowledge items.
* `string`: Represents simple textual data.

#### **Example Usage**

```typescript
const item1: KnowledgeItem = "Basic fact";

const item2: KnowledgeItem = {
  topic: "Mathematics",
  difficulty: "Intermediate"
};

const item3: KnowledgeItem = [
  "Introduction to AI",
  { topic: "Machine Learning", level: "Advanced" },
  [
    { title: "Deep Learning", examples: ["CNNs", "RNNs"] },
    "Neural Networks Overview"
  ]
];
```

#### **Key Features**

* **Recursive definition:** Enables deeply nested data structures.
* **Flexible typing:** Can accommodate strings, objects, or arrays interchangeably.
* **Useful for:** Knowledge graphs, document trees, JSON-based knowledge bases, or hierarchical content representations.



### **`Storage` Abstract Class**

```typescript
export abstract class Storage {
  // The `save` method stores a KnowledgeItem and potentially updates another one.
  abstract save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem>;

  // The `load` method returns a KnowledgeItem based on the `where` condition.
  abstract load(where: KnowledgeItem): Promise<KnowledgeItem | null>;
}
```

#### **Description**

The `Storage` class defines an **abstract interface** for persisting and retrieving `KnowledgeItem` data.
It provides two core asynchronous methods — `save` and `load` — that subclasses must implement to interact with a storage backend (e.g., a database, filesystem, or in-memory cache).

This abstraction allows flexible implementations of different storage mechanisms while maintaining a consistent interface for managing knowledge data.

---

#### **Methods**

##### **`save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem>`**

Stores or updates a `KnowledgeItem` in the underlying storage system.

* **Parameters:**

  * `item`: The `KnowledgeItem` to store or update.
  * `where`: A `KnowledgeItem` that specifies the location, criteria, or context where the `item` should be saved.

* **Returns:**
  A `Promise` resolving to the stored or updated `KnowledgeItem`.

* **Behavior:**
  Implementations may either:

  * Insert a new `KnowledgeItem` into storage, or
  * Modify an existing item identified by `where`.

---

##### **`load(where: KnowledgeItem): Promise<KnowledgeItem | null>`**

Retrieves a `KnowledgeItem` from storage that matches the given condition.

* **Parameters:**

  * `where`: A `KnowledgeItem` representing the lookup criteria (e.g., an ID, key, or filter object).
* **Returns:**
  A `Promise` resolving to:

  * The matching `KnowledgeItem` if found, or
  * `null` if no matching entry exists.

---

#### **Example Implementation**

```typescript
class InMemoryStorage extends Storage {
  private data: KnowledgeItem[] = [];

  async save(item: KnowledgeItem, where: KnowledgeItem): Promise<KnowledgeItem> {
    // Example: simplistic overwrite behavior
    this.data.push(item);
    return item;
  }

  async load(where: KnowledgeItem): Promise<KnowledgeItem | null> {
    // Example: naive match based on string equality
    return this.data.find(i => JSON.stringify(i) === JSON.stringify(where)) || null;
  }
}
```

---

#### **Use Cases**

* Implementing storage layers for:

  * Local or remote databases
  * File-based persistence
  * Cloud storage APIs
  * Caches or in-memory stores
* Defining a common interface for knowledge systems that manipulate structured or nested data.

---

Would you like me to rewrite this as **JSDoc comments directly above each method** (ready for IDE tooltips and documentation generation)?
