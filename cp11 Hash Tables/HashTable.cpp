#include<string>
#include<vector>
#include<iostream>
#include<memory>

using namespace std;
#define CAPACITY 50000

struct HashItem {
    string key;
    string value;

    HashItem(const string& key = "", const string& value = "") : key(key), value(value) {}

    bool IsEmpty() const{
        return key.empty() && value.empty();
    }
};


class HashLL{
public:
    HashItem item;
    unique_ptr<HashLL> next;

    HashLL(HashItem item) : item(item), next(nullptr) {}

    void InsertElement(HashItem Item) {
        if (item.IsEmpty() && !next) {
            this->item = Item;
        } else if (this->next == nullptr) {
            next = make_unique<HashLL>(Item);
        } else {
            next->InsertElement(Item);
        }
    }

    void RemoveElement(unique_ptr<HashLL> list){
        if(list->item.IsEmpty() && !list->next)
            return;
        if(!list->next)
            return;
        unique_ptr<HashLL> nextNode = std::move(list->next);
        list->item = nextNode->item;
        list->next = std::move(nextNode->next);
    }
    bool IsEmpty() const{
        return item.IsEmpty() && !next;
    }
};


class HashTable{
public:
    vector<HashItem> items;
    vector<unique_ptr<HashLL>> overflow_buckets;
    int size;
    int count;

    HashTable(int size) : size(size), count(0), items(size), overflow_buckets(size) {}
    unsigned long HashFunction(string str);
    void PrintTable(const HashTable& table);
    void InsertItem(const string& key, const string& value);
    void HandleCollision(unsigned long index, unique_ptr<HashItem> item);
    string Search(const string& key);
    void DeleteItem(const std::string& key);
};






unsigned long HashTable::HashFunction(string str){
    unsigned long res = 0;
    for (int i = 0; str[i]; i++)
        res += str[i];

    return res % CAPACITY;
}

void HashTable::PrintTable(const HashTable &table) {
    cout<<"Hash Table:"<<endl;
    for(int i = 0; i < table.size; i++){
        if(!table.items[i].IsEmpty()){
            std::cout << "Index: " << i
                      << ", Key: " << table.items[i].key
                      << ", Value: " << table.items[i].value
                      << std::endl;
        }
    }

}

void HashTable::InsertItem(const std::string &key, const std::string &value) {

    int index = this->HashFunction(key);

    if(this->items[index].IsEmpty()){
        //this place is free
        if(this->count == this->size){
            //table is full
            cout<<"Insertion Error: Current Hash Table is full"<<endl;
            return;
        }
        this->items[index] = HashItem(key,value);
        this->count++;
    }
    else{
        //Scenario 1, just update the value
        if(this->items[index].key == key){
            this->items[index].value = value;
        }
        else{
            HandleCollision(index, make_unique<HashItem>(key, value));
        }
    }
}

void HashTable::HandleCollision(unsigned long index, unique_ptr<HashItem> item) {
    unique_ptr<HashLL>& head = this->overflow_buckets[index];
    if(head->IsEmpty()){
        head->item = *item;
    }
    else{
        this->overflow_buckets[index]->InsertElement(*item);
    }
}

string HashTable::Search(const std::string &key) {
    int index = HashFunction(key);
    HashItem *item = &this->items[index];
    HashLL *head = this->overflow_buckets[index].get();
    if (!item->IsEmpty()) {
        if (item->key == key)
            return item->value;
        // Traverse the linked list in overflow_buckets[index]
        while (head) {
            if (head->item.key == key) {
                return head->item.value;
            }
            head = head->next.get(); // Move to the next node
        }
    }
    return ""; // If key is not found, return an empty string
}

void HashTable::DeleteItem(const std::string& key) {
    unsigned long index = HashFunction(key);

    // Check if key exists in the main items array
    if (!items[index].IsEmpty() && items[index].key == key) {
        items[index] = HashItem("", ""); // Reset the item
        return;
    }

    // Check the overflow bucket (linked list)
    if (overflow_buckets[index]) {
        HashLL* head = overflow_buckets[index].get();
        HashLL* prev = nullptr;

        while (head) {
            if (head->item.key == key) {
                // Remove the node from the linked list
                if (prev) {
                    prev->next = std::move(head->next);
                } else {
                    overflow_buckets[index] = std::move(head->next);
                }
                return;
            }
            prev = head;
            head = head->next.get();
        }
    }
}



/*
void testHashTable() {
    HashTable hashTable(CAPACITY);

    // Insert items
    hashTable.InsertItem("key1", "value1");
    hashTable.InsertItem("key2", "value2");
    hashTable.InsertItem("key3", "value3");

    // Print the hash table
    hashTable.PrintTable(hashTable);

    // Search for items
    cout << "Searching for key 'key1': " << hashTable.Search("key1") << endl;
    cout << "Searching for key 'key2': " << hashTable.Search("key2") << endl;
    cout << "Searching for key 'key4': " << hashTable.Search("key4") << endl;

    // Delete items
    hashTable.DeleteItem("key2");
    hashTable.DeleteItem("key4"); // key4 doesn't exist, no effect

    // Print the hash table after deletion
    hashTable.PrintTable(hashTable);

    // Assert statements to validate expected results
    assert(hashTable.Search("key2") == ""); // key2 should be deleted, should return ""
    assert(hashTable.Search("key4") == ""); // key4 doesn't exist, should return ""

    cout << "Tests completed successfully!" << endl;
}

int main() {
    testHashTable();
    return 0;
}

*/