#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<fstream>
#include <cstring>

using namespace std;

const int TABLE_SIZE = 10;

struct node
{
    char song[100];
    struct node *next;
    struct node *prev;
}*top,*temp,*top1;

void tofile(char a[])
{
    fstream f1;
    f1.open("playlist.txt",ios::out|ios::app);
    f1<<a;
    f1.close();
}

class Stack {
private:
    node* topdata;

public:
    Stack() : topdata(nullptr) {}

    bool isEmpty() {
        return topdata == nullptr;
    }

    void push(const char* newSong) {
        node* newNode = new node;
        strcpy(newNode->song, newSong);
        newNode->next = topdata;
        topdata = newNode;
    }

    string top() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return nullptr;
        }
        return topdata->song;
    }

    void pop() {
        if (isEmpty()) {
            cout << "Stack is empty. Cannot pop.\n";
            return;
        }
        node* temp = topdata;
        topdata = topdata->next;
        delete temp;
    }

    void display() {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }
        cout << "Stack Contents:\n";
        //node* current;
        while (!isEmpty()) {
            // current = top;
            // cout << current->song << "\n";
            // pop();
            cout<<top()<<endl;
            pop();

        }
    }

    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }
};

Stack searchHistory,playHistory;


class HashTable {
private:
    struct node *table[TABLE_SIZE];

    int hashFunction(const char *key) {
        int sum = 0;
        for (int i = 0; key[i] != '\0'; i++) {
            sum += key[i];
        }
        return sum % TABLE_SIZE;
    }

public:
    HashTable() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            table[i] = nullptr;
        }
    }

    void insert(const char *key) {
        int index = hashFunction(key);

        struct node *newNode = new node;
        strcpy(newNode->song, key);
        newNode->next = nullptr;
        newNode->prev = nullptr;

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            newNode->next = table[index];
            table[index]->prev = newNode;
            table[index] = newNode;
        }
    }

    void display() {
        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << "Bucket " << i << ": ";
            struct node *temp = table[i];
            while (temp != nullptr) {
                cout << temp->song << " -> ";
                temp = temp->next;
            }
            cout << "nullptr" << std::endl;
        }
    }

    bool search(const char *key) {
        int index = hashFunction(key);
        struct node *temp = table[index];

        while (temp != nullptr) {
            if (strcmp(temp->song, key) == 0) {
                return true; 
            }
            temp = temp->next;
        }
        return false;
    }
};

HashTable hashTable;

void add_node(struct node *first)
    {
    char a[100];
    while(first->next!=NULL)
    {
        first=first->next;
    }
    first->next=(struct node*)malloc(sizeof(struct node));
    first->prev=first;
    first=first->next;
    cout<<"\n\a\a\a\aEnter Song name-  ";
    scanf("%s",&a);
    hashTable.insert(a);
    strcpy(first->song,a);
    tofile(a);
    first->next=NULL;
}

void add_node_file(struct node *first,string a)
    {
    while(first->next!=NULL)
    {
        first=first->next;
    }
    first->next=(struct node*)malloc(sizeof(struct node));
    first->prev=first;
    first=first->next;
    strcpy(first->song,a.c_str());
    hashTable.insert(first->song);
    first->next=NULL;
}

void delete_file(char a[])
{
    fstream f1,f2;
    string line;
    int x=0;
    f1.open("playlist.txt",ios::in|ios::out);
    f2.open("temp.txt",ios::in|ios::out);
    while(!f1.eof())
    {
        getline(f1,line);
        if(strcmp(a,line.c_str())!=0)
        f2<<line<<endl;
        else if (strcmp(a,line.c_str())==0)
        x=1;
    }
    f1.close();
    f2.close();
    remove("playlist.txt");
    rename("temp.txt","playlist.txt");
    if(x==0)
        {
        cout << "There is no song with name you entered." << endl;
        }
    else
        {
        cout << "Song has been deleted." << endl;
        }
    }


void del_node(struct node *first)
{
    while((first->next)->next!=NULL)
    {
        first=first->next;
    }
    struct node *temp;
    temp=(first->next)->next;
    first->next=NULL;
    free(temp);
   cout<<"Deleted"<<endl;
}

void printlist(struct node *first)
{
    cout<<"\nPlaylist Name- ";
    while(first->next!=NULL)
    {
        cout<<first->song<<endl;
        first=first->next;
    }
    cout<<first->song<<endl;
}

void count_nodes(struct node *first)
{
    int i=0;
    while (first->next!=NULL)
    {
        first=first->next;
        i++;
    }
    i++;
    cout<<"\nTotal songs-  "<<i-1<<endl;
}

int count_nodes(struct node *first,int)
{
    int i=0;
    while (first->next!=NULL)
    {
        first=first->next;
        i++;
    }
    i++;
    return i-1;
}


struct node  *del_pos(struct node* &pointer, int pos)
{

           struct node *n1,*prev1,*temp;
           prev1= ( struct node *)malloc(sizeof(node));
           temp= (struct node *)malloc(sizeof(node));
           int i=0;
           n1 = pointer;
           if(pos==1)
           {
                temp=pointer;
                delete_file(temp->song);
                pointer=temp->next;
                pointer->prev = NULL;
                free(temp);
                printf("\nThe list is updated\nUse the display function to check\n");
                return pointer;
           }
           while(i<pos)
           {
               prev1=n1;
               n1=n1->next;
               i++;
            }

            if(n1->next==NULL)
            {

            temp=n1;
            delete_file(temp->song);

            prev1->next->prev=NULL;
            prev1->next=NULL;

            free(temp);
             printf("\nThe list is updated\nUse the display function to check\n");
          }

            else
            {
            temp=n1;
            delete_file(temp->song);
            prev1->next=temp->next;
            temp->next->prev=prev1;
            free(temp);
             printf("\nThe list is updated\nUse the display function to check\n");
            }

}

void search1(struct node *first)
{
    char song[100];
    cout<<"\n\a\a\a\aEnter song To be Searched- ";
    scanf("%s",&song);
    searchHistory.push(song);

    if (hashTable.search(song)) {
        cout<<"\n\a\a\a\a#Song Found"<<endl;
    } else {
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }
}

void create()
{
    top = NULL;
}

void push(char data[])
{
    if (top == NULL)
    {
        top =(struct node *)malloc(sizeof(struct node));
        top->next = NULL;
        strcpy(top->song,data);
    }
    else if (strcmp(top->song,data)!=0)
    {
        temp =(struct node *)malloc(sizeof(struct node));
        temp->next = top;
        strcpy(temp->song,data);
        top = temp;
    }

    //playHistory.push(data);
}

void display()
{
    top1 = top;
    if (top1 == NULL)
    {
        printf("\n\a\a\a\a=>NO recently played tracks.\n");
        return;
    }
    printf("\n\a\a\a\a#Recently played tracks-\n");
    while (top1 != NULL)
    {
        printf("%s", top1->song);
        printf("\n");
        top1 = top1->next;
    }
 }

void play(struct node *first)
{
    char song[100];
    printlist(first);
    cout<<"\n\a\a\a\aChoose song you wish to play- ";
    scanf("%s",song);
    int flag=0;

    while(first!=NULL)
    {
        if(strcmp(first->song,song)==0)
        {
            //playHistory.push(song);
            cout<<"\n\a\a\a\a=>Now Playing......"<<song<<endl;
            flag++;
            push (song);
            break;
        }
        else
        {
            first=first->next;
        }
    }
    if(flag==0)
    {
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }
}

void recent()
{
display();
}

void topelement()
{
    top1=top;
    if(top1==NULL)
    {
        printf("\n\a\a\a\a#NO last played tracks.\n");
        return;
    }
    cout<<"\n=>Last Played Song - "<<top->song<<endl;
}

// struct node *partition(struct node *left, struct node *right)
// {
//     struct node *pivot = right;
//     struct node *i = left->prev;
//     for (struct node *ptr = left; ptr != right; ptr = ptr->next)
//     {
//         if (ptr->song <= pivot->song)
//         {
//             i = (i == NULL ? left : i->next);
//             char temp[100];
//             strcpy(temp,i->song);
//             strcpy(i->song,ptr->song);
//             strcpy(ptr->song,temp);
//         }
//     }
//     i = (i == NULL ? left : i->next);
//     char temp[100];
//     strcpy(temp,i->song);
//     strcpy(i->song ,pivot->song);
//     strcpy(pivot->song,temp);
//     return i;
// }
// void QuickSort(struct node *left, struct node *right)
// {
//     if (right != NULL && left != right && left != right->next)
//     {
//         struct node *p = partition(left, right);
//         QuickSort(left, p->prev);
//         QuickSort(p->next, right);
//     }
// }
// void sort(struct node* &song)
// {   
//     struct node* tail = song;
//     struct node* head = song;
//     while(tail->next != NULL){
//         tail = tail->next;
//     }
//     QuickSort(head,tail);
// }

void swap(struct node *a, struct node *b) {
    char temp[100];
    strcpy(temp, a->song);
    strcpy(a->song, b->song);
    strcpy(b->song, temp);
}


void sort(struct node *start) {
    int swapped;
    struct node *ptr;
    struct node *last = nullptr;

    if (start == nullptr)
        return;

    do {
        swapped = 0;
        ptr = start;

        while (ptr->next != last) {
            if (strcmp(ptr->song, ptr->next->song) > 0) {
                swap(ptr, ptr->next);
                swapped = 1;
            }
            ptr = ptr->next;
        }
        last = ptr;
    } while (swapped);
}

void addplaylist(struct node *start)
{
    fstream f1;
    string line;
    f1.open("playlist.txt",ios::in);
    while(!f1.eof())
    {
        getline(f1,line);
        add_node_file(start,line);
    }
    cout<<"Playlist Added"<<endl;
    f1.close();
}

void del_search(struct node *&start)
{
    char song[100];
    printlist(start);
    cout<<"\n\a\a\a\aChoose song you wish to delete- ";
    scanf("%s",song);
    
    int flag=0;

    if(strcmp(start->song,song)==0)
        {
            cout<<"\n\a\a\a\a#Song Found"<<endl;
            struct node *temp;
            temp= (struct node *)malloc(sizeof(node));
            temp=start;
            delete_file(temp->song);
            start = temp->next;
            temp->next = NULL;
            free(temp);
            flag++;
            return;
        }

            struct node *trav;
            trav= (struct node *)malloc(sizeof(node));
            trav=start;

    while(trav!=NULL)
    {
        if(strcmp(trav->song,song)==0)
        {
            cout<<"\n\a\a\a\a#Song Found"<<endl;
            // struct node *temp;
            // temp= (struct node *)malloc(sizeof(node));
            // temp=trav;
            delete_file(trav->song);
            (trav->prev)->next=trav->next;
            (trav->next)->prev=trav->prev;
            trav->next=NULL;
            trav->prev=NULL;
            free(trav);
            flag++;
            return;
        }
        else
        {
            trav=trav->next;
        }
    }
    if(flag==0)
    {
        cout<<"\n\a\a\a\a#Song Not found"<<endl;
    }
}

void push(node** head_ref, node* new_node)
{

    new_node->prev = NULL;
  
    new_node->next = (*head_ref);
  

    if ((*head_ref) != NULL)
        (*head_ref)->prev = new_node;
  
    (*head_ref) = new_node;
}

node* revKG(node* head, int k)
{
    node *current = head;
    node* next = NULL;
    node* newHead = NULL;
    int count = count_nodes(head,1);
     

    if (next != NULL)
    {
        head->next = revKG(next, k);
        head->next->prev = head;
    }
     
    newHead->prev = NULL;
    return newHead;
}

void push(struct node **head_ref, char new_song[]) {
    struct node *new_node = new node;
    strcpy(new_node->song, new_song);
    new_node->prev = nullptr;
    new_node->next = *head_ref;

    if (*head_ref != nullptr)
        (*head_ref)->prev = new_node;

    *head_ref = new_node;
}



void playloop(struct  node* &start)
{

    struct node* trav = start;
JUMP:
    while(trav!=NULL){
        push(trav->song);
        cout<<"\n\a\a\a\a=>Now Playing......"<<trav->song<<endl;
        trav = trav->next;
    }

    bool flag = 0;
    cout<<"\n#Want to replay in-LOOP: \n0. No\n1. Yes\n";
    cin>>flag;
    if(flag)
    {
        trav = start;
        goto JUMP;
    }
    else
    {
        return;
    }
}

void shuffleplay(struct node* &start)
{
    int count = count_nodes(start,1);
    start = revKG(start,count/2);
    start = revKG(start,count/3);
    playloop(start);
}


void loop(struct node* &start)
{
    int check;
    step1:
    cout<<"\nYou wish to play in......\n1.Regular Loop\n2.Shuffled Loop\n";
    cin>>check;
    if(check == 1)
    {
        playloop(start);
    }
    else if(check == 2)
    {
        shuffleplay(start);
    }
    else
    {
        cout<<"Invalid Input!\n";
        goto step1;   
    }
}

void deletemenu(struct node *&start)
{
    int c;
    cout<<"Which type of delete do you want?\n1.By Search\n2.By Position"<<endl;
    cin>>c;
    switch(c)
    {
    case 1: del_search(start);
            return;
    break;
    case 2: int pos;
            printf("\nEnter the pos of the song : ");
            scanf("%d",&pos);
            del_pos(start,pos-1);
            return;
    break;
    default:
    cout<<"Invalid Input!"<<endl;
    }
}

main()
{

    char song[100];
    struct node *start,*hold;
    start=(struct node *) malloc(sizeof(struct node));
    cout<<"\t\t\t\a\a\a\a**WELCOME**"<<endl;
    cout<<"\n**please use '_' for space."<<endl;
    cout<<"\n\n\a\a\a\aEnter your playlist name-  ";
    cin.getline(start->song,100);
    start->next=NULL;
    hold=start;
    create();

    int choice;
    string t;
    do{

        cout<<"\n1.Add  New Song\n2.Delete Song\n3.Display Entered Playlist\n4.Total Songs\n5.Search Song\n6.Play Song\n7.Recently Played List\n8.Last Played\n9. Sorted playlist\n10.Add From File\n11.Loop Play\n12.Get Search History\n13.Exit"<<endl;
        cout<<("\n\a\a\a\aEnter your choice- ");
        cin>>choice;
        switch(choice)
        {
            case 1:add_node(start);
            break;
            case 2:deletemenu(start);
            break;
            case 3:printlist(start);
            break;
            case 4:count_nodes(hold);
            break;
            case 5:search1(start);
            break;
            case 6:play(start);
            break;
            case 7:recent();
            break;
            case 8:topelement();
            break;
            case 9:sort(start->next);
                    printlist(start);
            break;
            case 10:addplaylist(start);
            break;
            case 11:loop(start);
            break;
            case 12:searchHistory.display();
            break;
            case 13:exit(0);
        }
    }while(choice!=12);


}