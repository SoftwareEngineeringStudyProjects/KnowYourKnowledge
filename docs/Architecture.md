## General Moments

### Everything is a Knowledge Item. 
#### KnowledgeItem 
KnowledgeItem - abstract class, that is parental for all other items

**Unique fields: title, creation_time,  id**


### Information Classes 
These classes, such as TextNote, Comment, etc. are inherited from KnowledgeItem. Their main function – to store a specific type of information. 

Documentation and description for each specific class could be found (in future) in InformationClasses directory? Or maybe in Doxygen-generated documentation? 


### Collection Classes
#### Collection? : Inherited from KnowledgeItem
Collection—abstract class to store other items. Inherited from KnowledgeItem. 

**Additional fields: container :  can store objects of different types, but all of them are inherited from KnowledgeItem.** 

#### Other Collection classes
Other collection classes, such as Directory and TextNoteCollection are inherited from Collection.

Documentation and description for each specific class could be found (in future) in CollectionClasses directory

### Storage API
We want to support saving KnowledgeItems to different storages and loading from these storages. Examples of storages include:
* Single file (or other stream, such as std::cout/std::cin or string)
  * Maybe supporting different formats, such as plain text or JSON or configurable formats
* File system - storing as directories and files
* Git repository
* Cloud storages such as Google Docs
* Stream of events ordered by Timestamps
* ...

This should be implemented with storage API. Currently under development.

Storage API requires double dispatch - behavior should depend on 1) type of KnowledgeItem and 2) type of storage. Something similar to Visitor pattern may be needed. Using RTTI such as `dynamic_cast` or `typeid` is possible, but should be used only if other alternatives are significantly more complex and/or less capable.

### Other Classes 
This classes implement specific functions, such as loading/exporting items etc. and are not inherited from KnowledgeItem


### Comments
1) id in KnowledgeItem - should have   **id_T**  that is synonym to **base32**  type
