
int main(){
    bool login = logging();
    if(!login){
        cout << "Login failed please try again " << endl;
        return 0;
    }else{
        cout << "Login successful! " << endl;
        return 1;
    }
}