// Author: Aayush Keshari
// M Number: 15039880
// Email: kesharah@mail.uc.edu
// --------------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>

template <typename T>
class DoubleLinkedList {
private:
    struct Node {
        T* data;
        Node* next;
        Node* prev;

        Node(T* item) : data(item), next(nullptr), prev(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

    Node* findNode(const T& item) {
        Node* current = head;
        while (current) {
            if (*(current->data) == item) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

public:
    DoubleLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoubleLinkedList() {
        while (!IsEmpty()) {
            T* item = RemoveAt(0);
            delete item;
        }
    }

    void AddItem(T* item) {
        Node* newNode = new Node(item);
        if (IsEmpty() || *item < *(head->data)) {
            newNode->next = head;
            if (head) head->prev = newNode;
            head = newNode;
        }
        else {
            Node* current = head;
            while (current->next && *(current->next->data) < *item) {
                current = current->next;
            }
            newNode->next = current->next;
            if (current->next) current->next->prev = newNode;
            current->next = newNode;
            newNode->prev = current;
        }
        if (!tail) {
            tail = newNode;
        }
        size++;
    }

    T* GetItem(const T& item) {
        Node* found = findNode(item);
        if (found) {
            if (found == head) {
                head = found->next;
            }
            else {
                found->prev->next = found->next;
            }
            if (found == tail) {
                tail = found->prev;
            }
            else {
                found->next->prev = found->prev;
            }
            T* data = found->data;
            delete found;
            size--;
            return data;
        }
        return nullptr;
    }

    bool IsInList(const T& item) {
        return findNode(item) != nullptr;
    }

    bool IsEmpty() const {
        return size == 0;
    }

    int Size() const {
        return size;
    }

    T* SeeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }
        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    T* SeeNext() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty");
        }
        static Node* current = head;
        if (!current) {
            return nullptr;  
        }
        T* data = current->data;
        current = current->next;
        return data;
    }

    T* SeePrev() {
        if (IsEmpty()) {
            throw std::runtime_error("List is empty");
        }
        static Node* current = tail;
        if (!current) {
            return nullptr;  
        }
        T* data = current->data;
        current = current->prev;
        return data;
    }

    T* RemoveAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }

        if (current == head) {
            head = current->next;
        }
        else {
            current->prev->next = current->next;
        }

        if (current == tail) {
            tail = current->prev;
        }
        else {
            current->next->prev = current->prev;
        }

        T* data = current->data;
        delete current;
        size--;

        return data;
    }

    void Reset() {
        static Node* current = head;
    }
};

class Part {
private:
    int SKU;
    std::string Description;
    double Price;
    std::string UOM;
    int QuantityOnHand;
    int LeadTime;

public:
    Part(int sku, const std::string& desc, double price, const std::string& uom, int quantity = 0)
        : SKU(sku), Description(desc), Price(price), UOM(uom), QuantityOnHand(quantity), LeadTime(0) {}

    std::string GetPartInfo() const {
        return std::to_string(SKU) + " " + Description;
    }

    double GetPrice() const {
        return Price;
    }

    bool InStock() const {
        return QuantityOnHand > 0;
    }

    bool operator>(const Part& other) const {
        return SKU > other.SKU;
    }

    bool operator<(const Part& other) const {
        return SKU < other.SKU;
    }

    bool operator==(const Part& other) const {
        return SKU == other.SKU;
    }
};



int main() {
    DoubleLinkedList<Part> partList;

    while (true) {
        int choice;
        std::cout << "Menu:\n";
        std::cout << "1. Add Item\n";
        std::cout << "2. Get Item\n";
        std::cout << "3. Check If Item is In List\n";
        std::cout << "4. Is List Empty\n";
        std::cout << "5. Get List Size\n";
        std::cout << "6. See Item At\n";
        std::cout << "7. See Next Item\n";
        std::cout << "8. See Previous Item\n";
        std::cout << "9. Reset\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            int sku;
            std::string desc;
            double price;
            std::string uom;
            int quantity;

            std::cout << "Enter the Stock Keeping Number (SKU): ";
            std::cin >> sku;
            std::cout << "Enter the description of the item: ";
            std::cin.ignore();
            std::getline(std::cin, desc);
            std::cout << "Enter the price of the item: ";
            std::cin >> price;
            std::cout << "Enter the unit of measure (UOM): ";
            std::cin >> uom;
            std::cout << "Enter the quantity on hand: ";
            std::cin >> quantity;

            Part* newPart = new Part(sku, desc, price, uom, quantity);
            partList.AddItem(newPart);
            break;
        }

        case 2: {
            int sku;
            std::cout << "Enter SKU to get: ";
            std::cin >> sku;
            Part item(sku, "", 0, "");
            Part* retrieved = partList.GetItem(item);
            if (retrieved) {
                std::cout << "Item Retrieved: " << retrieved->GetPartInfo() << std::endl;
                delete retrieved;
            }
            else {
                std::cout << "Item not found." << std::endl;
            }
            break;
        }

        case 3: {
            int sku;
            std::cout << "Enter SKU to check: ";
            std::cin >> sku;
            Part item(sku, "", 0, "");
            bool isInList = partList.IsInList(item);
            std::cout << "Item is " << (isInList ? "in" : "not in") << " the list." << std::endl;
            break;
        }

        case 4: {
            bool isEmpty = partList.IsEmpty();
            std::cout << "List is " << (isEmpty ? "empty" : "not empty") << std::endl;
            break;
        }

        case 5: {
            int size = partList.Size();
            std::cout << "List size: " << size << std::endl;
            break;
        }

        case 6: {
            int index;
            std::cout << "Enter index to see: ";
            std::cin >> index;
            try {
                Part* item = partList.SeeAt(index);
                std::cout << "Item at index " << index << ": " << item->GetPartInfo() << std::endl;
            }
            catch (const std::out_of_range& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
            break;
        }

        case 7: {
            Part* item = partList.SeeNext();
            if (item) {
                std::cout << "Next item: " << item->GetPartInfo() << std::endl;
            }
            else {
                std::cout << "Reached the end of the list." << std::endl;
            }
            break;
        }

        case 8: {
            Part* item = partList.SeePrev();
            if (item) {
                std::cout << "Previous item: " << item->GetPartInfo() << std::endl;
            }
            else {
                std::cout << "Reached the beginning of the list." << std::endl;
            }
            break;
        }

        case 9: {
            partList.Reset();
            break;
        }

        case 0:
            return 0;

        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }

    return 0;
}
