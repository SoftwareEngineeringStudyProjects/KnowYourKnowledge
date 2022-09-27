## General Moments

### Everything is a Knowledge Item. 
#### KnowledgeItem 
KnowledgeItem - abstract class, that is parental for all other items
**Unique fields: _title, creation_time,  id: **


### Information Classes 

#### TextNote: Inherited from KnowledgeItem
Storage class for text information. TextNote inherited from KnowledgeItem. 
**Additional fields: string_text

#### Comment: Inherited from KnowledgeItem
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam ultricies sit amet sapien in posuere. Maecenas accumsan dui ut diam molestie, sed consectetur libero eleifend. Suspendisse potenti

#### Image : Inherited from KnowledgeItem
Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nam ultricies sit amet sapien in posuere. Maecenas accumsan dui ut diam molestie, sed consectetur libero eleifend. Suspendisse potenti


### Storage Classes
#### Storage : Inherited from KnowledgeItem
Storage - abstract class to store other items. Inherited from KnoweledgeItem. 
**Additional fields: container that can store objects of different types, but all of them are inherited from KnowledgeItem 

#### Directory : Inherited from Storage
Same as storage, but can't contain a Storage objects.

#### TextNoteCollection: Inherited from Storage.
Can store only TextNote objects.


### Other Classes 
#### LocalStream
LocalStream static class that implements methods to load and export all kinds of items. Main idea – it operates only with local files.


### Comments
1) id in KnowledgeItem - should have   **id_T**  that is synonym to **base32**  type
