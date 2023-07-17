#include <iostream>

class Gun{
    private:
        std::string name;
        int maxammo;
        int magammo;

    public:

    //constructs gun with name,capacity and a loaded mag
    Gun(std::string n,int maxa){
        name = n;
        maxammo = maxa;
        magammo = maxa;
    }

    std::string Getname(){
        return name;
    }

    int Getmagammo(){
        return magammo;
    }

    //checks if mag has bullets,fires
    void Fire(){
        if(magammo > 0){
            std::cout<<"pew"<<std::endl;
            magammo--;
        }
        else{
            std::cout<<"clack,out of ammo"<<std::endl;
        }
    }

    //reloads the mag
    void Reload(){
        std::cout<<"Reloading!!"<<std::endl;
        magammo = maxammo;
    }
};

//gets a possitive number from a user in a range of 0 to size
int getUNum(int size){
	int num;
		
    if(!(std::cin >> num)){//not a number
    	num = -1;
	}else{
		if(!(num>= 0 && num < size)){//out of bounds
			num = -2;
		}
	}
    
    std::cin.clear();
    std::cin.ignore(123,'\n');
    
	return num;
}

//changes the selected gun from main
int Selectgun(Gun g[],int size){

    //displays your options
    std::cout<<"Please select your gun:\n";
    for(int i=0;i < size;i++){
        std::cout << i << ": " + g[i].Getname()<< std::endl;
    }

    //checks for valid input
    int selectnum;
	do{
		selectnum=getUNum(size);
		/*
        debug
		if(selectnum<0)
			std::cout << "Error Code : " << snum << std::endl;
        */    
	}while(selectnum<0);
	
	return selectnum;
	
}

int main(){

    
    Gun guns[]{
           Gun("Revolver",6),
           Gun("M1911",20)
    };

    //find how many guns we got and runs the function
    int sizeofguns = sizeof(guns) / sizeof(guns[0]);
    int selectedgun=Selectgun(guns,sizeofguns);

    bool exit = true;
    int ans;
    std::cout << "You can fire,reload,see how much ammo is left by typing:\n"
    << "0:Exit\n1:Fire\n2:reload\n3:check\n4:change gun" <<std::endl;
    do{
    	int ans;
        do{
			ans=getUNum(5);
			//debug
			//std::out << ans << std::endl;
		}while(ans<0);
		
        switch(ans){
            case 0:
                exit = false;
                break;
            case 1:
                guns[selectedgun].Fire();
                break;
            case 2:
                guns[selectedgun].Reload();
                break;
            case 3:
                std::cout << guns[selectedgun].Getmagammo() << std::endl;
                break;
            case 4:
                selectedgun=Selectgun(guns,sizeofguns);
                std::cout << "You can fire,reload,see how much ammo is left by typing:\n"
                << "0:Exit\n1:Fire\n2:reload\n3:check\n4:change gun" <<std::endl;
                break;
        }
    }while(exit);
    return 0;
}