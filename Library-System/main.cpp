#include<iostream>
#include<algorithm>
using namespace std;
struct book{
    int id,quantity,borrowcnt=0;
    string name;
};
struct user{
    int id;
    string name,borrowed_books[100] ;
};
book bookdata[10000];
user userdata[10000];
int book_cnt=0;
int user_cnt=0;

bool cmp_by_id(const book & x,const book & y){
    
        if (x.id <y.id)
            return true;
        return false;
    }
bool cmp_by_name(const book & x,const book &y){
    return x.name < y.name;
    
}
struct backend{
      
 
    void add_book(){
       cin>>bookdata[book_cnt].id>>bookdata[book_cnt].name>>bookdata[book_cnt].quantity;
       book_cnt++;
       

    }
    void add_user(){
        cin>>userdata[user_cnt].name>>userdata[user_cnt].id;
        user_cnt++;

    }
    void borrow(){
      string name,bookname;
      cin>>name>>bookname;
      bool isfound = false;
      for (int i =0; i <book_cnt; i++){
    
        if (bookname == bookdata[i].name){
            isfound = true;
            if (bookdata[i].quantity == 0){
                cout<<"Sorry,no available copies\n";
                return;
            }
            bookdata[i].borrowcnt+=1;
            bookdata[i].quantity--;
            for(int j=0; j <user_cnt; j++){
                if (name == userdata[j].name){

                    for (int x =0; x <100; x++){
                        if (userdata[j].borrowed_books[x] == ""){
                           userdata[j].borrowed_books[x] = bookname;
                           break;
                        }
                    }

                }
             
            }
               break;

        }
      }
      if (!isfound ){
        cout<<"Book not found\n";
      }

    }
    void borrowed_by_name(){
        
        string bookname;
        cin>>bookname;
        bool isfound=false;
        for (int i =0; i <user_cnt; i++){
            for (int x =0; x <100; x++){
                if (userdata[i].borrowed_books[x] == bookname){
                    cout<<userdata[i].name<<endl;
                    isfound= true;
                    break;

                }
            }
            
        }

        if (!isfound){
            cout<<"there is no user borrowed this book\n";
        }
    }
    void return_book(const string & name,const string & bookname ){
             for (int i =0; i <user_cnt; i++){
                if (userdata[i].name == name){
                    for (int j =0; j <100; j++){
                        if (userdata[i].borrowed_books[j] == bookname){
                            for (int x = j; x < 99; x++){
                                userdata[i].borrowed_books[x]=userdata[i].borrowed_books[x+1];
                            }
                           userdata[i].borrowed_books[99] = ""; 
                           for (int y =0; y < book_cnt; y++){
                            if (bookdata[y].name == bookname){
                       
                             bookdata[y].quantity+=1;
                             break;
                    }
                    }
                    return;
                        }
                    }
                }
                
             }
      

    }
    bool is_prefix(const string & bookname,const string & pre){
        int len = pre.size();
        if (len >bookname.size()){
            return false;
        }
      for (int i =0; i < len ;i++){
        if (pre[i] != bookname[i]){
            return false;
        }
      }
      return true;
    }
    void search_by_prefix(const string & pre){
        bool isfound=false;
       for (int i =0; i <book_cnt; i++ ){
        if (is_prefix(bookdata[i].name,pre)){
            cout<<bookdata[i].name<<endl;
            isfound = true;

        }
       }
       if(!isfound){
        cout<<"No books with such prefix\n";
       }

    }

    void print_by_id(const book bookdata[]){
        book cpy[book_cnt];
        for(int i =0; i <book_cnt; i++){
            cpy[i]=bookdata[i];
        }
        sort(cpy,cpy+book_cnt,cmp_by_id);
        for (int i =0; i <book_cnt; i++){
            cout<<"id = "<<cpy [i].id<<" name = "<<cpy[i].name<<" total_quantity "<<cpy[i].quantity<<" total_borrowed "<<cpy[i].borrowcnt<<endl;
        }

    }
    void print_by_name(const book bookdata[]){
       book cpy[book_cnt];
        for(int i =0; i <book_cnt; i++){
            cpy[i]=bookdata[i];
        }
        sort(cpy,cpy+book_cnt,cmp_by_name);
        for (int i =0; i <book_cnt; i++){
          cout<<"id = "<<cpy [i].id<<" name = "<<cpy[i].name<<" total_quantity "<<cpy[i].quantity<<" total_borrowed "<<cpy[i].borrowcnt<<endl;

        }
    }
    void print_users(){
         for (int i =0; i <user_cnt; i++){
            cout<<"user "<<userdata[i].name <<" ID "<<userdata[i].id<<" borrowed books ids: ";
            for (int x =0; x <100; x++){
                if (userdata[i].borrowed_books[x] != ""){
                    for (int j =0; j <book_cnt; j++){
                        if (userdata[i].borrowed_books[x] == bookdata[j].name){
                            cout<<bookdata[j].id<<" ";
                            break;
                        }
                    }
                }else{
                    cout<<"\n";
                    break;
                }
            }
         }
    }


};
backend backendoperations;
struct frontend{
    
     void menu(){

    cout<<"Library menu:\n\
1) add book\n\
2) search_books_by_prefix\n\
3) print_who_borrowed_book_by_name\n\
4) print_library_by_id\n\
5) print_library_by_name\n\
6) add user\n\
7) user_borrow_book\n\
8) user_return_book\n\
9) print_users\n\
10) Exit\n";
    int choice;
    while (true){
    cout<<"Enter your menu choice [1 - 10]: ";
    cin>>choice;
    if (choice <1 || choice >10){
        cout<<"Invalid input.\nplease try again.\n";
        continue;
    }else{
        
        if (choice == 1){
            cout<<"Enter book info: id & name & total quantity: ";
            backendoperations.add_book();
        }else if(choice == 2){
            string prefix;
            
            cout<<"Enter book name prefix: ";
            cin>>prefix;
            backendoperations.search_by_prefix(prefix); 
        }else if(choice == 3){
            cout<<"Enter book name: "; 
             backendoperations.borrowed_by_name();
        }else if(choice == 4){
            backendoperations.print_by_id(bookdata);
        }else if (choice == 5){
            backendoperations.print_by_name(bookdata);

        }else if (choice == 6){
            cout<<"Enter user name & national id: ";
            backendoperations.add_user();
        }else if (choice == 7){
           cout<<"Enter user name and book name: ";

           backendoperations.borrow();
        }else if (choice == 8){
         string name,bookname;
         cout<<"Enter user name and book name: ";
         cin>>name>>bookname;
            backendoperations.return_book(name,bookname);
        }else if (choice == 9){
            backendoperations.print_users();
        }else {
            cout<<"Exiting program.....";
            return;
        }

    }
} 
}
};

int main(){
    frontend run;
    run.menu();

}
