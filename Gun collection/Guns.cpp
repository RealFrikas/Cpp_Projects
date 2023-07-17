#include <iostream>

class Gun{
    private:
        std::string name;
        int maxammo;
        int magammo;
        int mode = 0;
        bool single,burst,automatic;
    public:

    //constructs gun with name,capacity,a loaded mag , and available modes
    Gun(std::string n,int maxa,bool s,bool b,bool a){
        name = n;
        maxammo = maxa;
        magammo = maxa;
        single = s;
        burst = b;
        automatic = a;
        if(s == false){
            if(b == true){
                mode = 1;
            }
            else{
                mode = 2;
            }
        }
    }

    std::string Getname(){
        return name;
    }

    int Getmagammo(){
        return magammo;
    }

    void Changemode(){//cycle modes
        if(single == true && ((mode == 1 && automatic == false) || (mode == 2))){
            mode = 0;
            std::cout << "Mode changed to single shot!" << std::endl;
        }
        else if(burst == true && ((mode == 2 && single == false) || (mode == 0))){
            mode = 1;
            std::cout << "Mode changed to burst!" << std::endl;
        }
        else if (automatic == true && ((mode == 0 && burst == false) || (mode == 1))){
            mode = 2;
            std::cout << "Mode changed to automatic!" << std::endl;
        }
        else{
            std::cout << "Cannot change mode!" << std::endl;
        }
    }

    //checks if mag has bullets,fires
    void Fire(){
        //time between pew
        if(magammo > 0){
            //string soundeffect
            std::cout<<"pew"<<std::endl;
            magammo--;
        }
        else{
            std::cout<<"clack"<<std::endl;
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
           Gun("Revolver",6,true,false,false),
           Gun("M1911",7,true,false,false),
           Gun("FAMAS",30,false,true,true)
    };

    //find how many guns we got and runs the function
    int sizeofguns = sizeof(guns) / sizeof(guns[0]);
    int selectedgun=Selectgun(guns,sizeofguns);

    bool exit = true;
    int ans;
    std::cout << "You can fire,reload,see how much ammo is left by typing:\n"
    << "0:Exit\n1:Fire\n2:reload\n3:check\n4:change gun\n5:Change mode" <<std::endl;
    do{
    	int ans;
        do{
			ans=getUNum(6);
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
            case 5:
                guns[selectedgun].Changemode();
                break;
        }
    }while(exit);
    return 0;
}