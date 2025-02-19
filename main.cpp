#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <windows.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "17062004";
const char* DB = "db";

class Inventory{
	private:
		int Id, Quantity;
		string Name;
		float Price;
	public:
	Inventory():Id(0),Name(""),Quantity(0),Price(0.0) {}
	
	void setId(int id){
		Id = id;
	}
	
 void setName(string name){
	Name=name;
 }	
	
 void setQuantity(int quantity){
	Quantity=quantity;
 }
	
 void setPrice(float price){
	Price= price;
 }	
 
 //getter fucntions
 
 int getId(){
 	return Id;
 }
	
 string getName(){
    return Name;
 }
	
 int getQuantity(){
     return Quantity;
 }
	
 float getPrice(){
  return Price;
 }
};

//insert function
insertS(MYSQL* conn, Inventory u){
	 int id,quantity;
 string name;
 float price;
 
 cout<<"Enter Id: ";
 cin>>id;
 u.setId(id);
 
  cout<<"Enter Name: ";
 cin>>name;
 u.setName(name);

 cout<<"Enter Quantity: ";
 cin>>quantity;
 u.setQuantity(quantity);

 cout<<"Enter Price: $";
 cin>>price;
 u.setPrice(price);
 
 int iId= u.getId();
 int iQuantity= u.getQuantity();
 float fPrice = u.getPrice();
 
 stringstream ss;
 ss<<iId;
 string sId = ss.str();
 
 stringstream qs;
 qs<<iQuantity;
 string sQuantity = ss.str();
 
  stringstream as;
 as<<fPrice;
 string sPrice= as.str();
 
 string ins= "INSERT INTO product (Id, Name, Quantity, Price) VALUES ('"+sId+"', '"+u.getName()+"', '"+sQuantity+"', '"+sPrice+"')";
 if(mysql_query(conn,ins.c_str())){
 	cout<<"Error: "<<mysql_error(conn)<<endl;
 }
 else{
 	cout<<"Data Inserted Successfuly."<<endl;
 }
 Sleep(3000);
}

//show function

showRecord(MYSQL* conn){
	cout<<"ID||NAME||QUANTITY||PRICE"<<endl;
string show= "SELECT * FROM product";
 if(mysql_query(conn,show.c_str())){
 	cout<<"Error: "<<mysql_error(conn)<<endl;
 }
 else{
 	MYSQL_RES* res ;
 	res = mysql_store_result(conn);
 	if(res){
 	int num = mysql_num_fields(res);
 	MYSQL_ROW row;
 	while(row=mysql_fetch_row(res)){
 		for(int i=0; i< num; i++){
 		cout<<" "<<row[i];
		 }
		 cout<<endl;
	 }
	 }
 }
 Sleep(5000);
}

//search function
searchS(MYSQL* conn){
	 int id;
 cout<<"Enter Product ID: ";
 cin>>id;
 	
 stringstream ss;
 ss<<id;
 string sId= ss.str();
 
 string show = "SELECT * FROM product WHERE Id ='"+sId+"' ";
 if(mysql_query(conn,show.c_str())){
cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
MYSQL_RES* res;
res = mysql_store_result(conn);
if(res){
	MYSQL_ROW row = mysql_fetch_row(res);
if(row){
	int num = mysql_num_fields(res);
	for(int i=0; i<num; i++){
		cout<<" "<<row[i];
	}
}
mysql_free_result(res);
}
}
Sleep(5000);
}

// update function

updateS(MYSQL* conn, Inventory u){
	int id;
	cout<<"Enter Id: ";
	cin>>id;
	
	int iId = u.getId();
	 stringstream ss;
 ss<<id;
 string sId= ss.str();
 
 
  int quantity;
 cout<<"Enter New Quantity: ";
 cin>>quantity;
 u.setQuantity(quantity);
 
 int iQuantity = u.getQuantity();
	 stringstream qs;
 qs<<quantity;
 string sQuantity= qs.str();
 
 string upd = "UPDATE product SET Quantity = '"+sQuantity+"' WHERE Id = '"+sId+"'";
 if(mysql_query(conn,upd.c_str())){
cout<<"Error: "<<mysql_error(conn)<<endl;
}

else{
 cout<<"Data Updated Successfuly"<<endl;
}
Sleep(3000);
}

//delete function

deleteS(MYSQL* conn){
 int id;
 cout<<"Enter Product ID: ";
 cin>>id;
 	

 stringstream ss;
 ss<<id;
 string sId= ss.str();	
 
 string del = "DELETE FROM product WHERE Id ='"+sId+"' ";
 if(mysql_query(conn,del.c_str())){
 cout<<"Error: "<<mysql_error(conn)<<endl;
}

else{
 cout<<"Data Deleted"<<endl;
}
Sleep(3000);
}

int main() {
	
	Inventory u;
	
MYSQL* conn;
conn = mysql_init(NULL);

if(!mysql_real_connect(conn,HOST,USER,PW,DB,3306,NULL,0)){
	cout<<"Error: "<<mysql_error(conn)<<endl;
}
else{
	cout<<"Opening inventory mangement system....."<<endl;
}
Sleep(3000);

bool exit = false;
while(!exit){
	system("cls");
	int val;
	cout<<"Welcome to Inventory Management System"<<endl;
	cout<<"***************************************"<<endl;
	cout<<"1. Insert Product Data"<<endl;
	cout<<"2. Show Product Data"<<endl;
	cout<<"3. Search Product Data"<<endl;
 	cout<<"4. Update Product Data"<<endl;
 	cout<<"5. Delete Product Data"<<endl;
 	cout<<"0. Exit"<<endl;
 	cout<<"Enter choice: ";
 	cin>>val;
 	
 	cout<<endl;
 	
 	if(val==1){
 	insertS(conn,u);	
	 }
	 
	else if(val==2){
	showRecord(conn);	
	}
	
	else if(val==3){
	searchS(conn);	
	}
	
	else if(val==4){
	updateS(conn,u);	
	}
	
	else if(val==5){
	deleteS(conn);	
	}
	`
	else if(val==0){
		exit = true;
		cout<<"Good Luck!"<<endl;
		Sleep(3000);
	}
	else{
		cout<<"Invalid Input"<<endl;
		Sleep(300);
	}
}

    return 0;
}
