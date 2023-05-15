#include <iostream>
#include <fstream>
using namespace std;


void print(char **map, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cout<<map[i][j]<<" ";
        }
        cout<<"\n";
    }
    cout<<"\n\n";
}


bool validator(char **map, int n, int m, char o, int bound_N, int bound_M){
    switch (o)
    {
        case 'w':{
            if(map[n-1][m]!='X' && n-1 > 0)
            return true;
            else return false;

            break;
        }
        case 'a':{
            if(map[n][m-1]!='X' && m-1 > 0)
            return true;
            else return false;

            break;
        }
        case 's':{
            if(map[n+1][m]!='X' && n+1 < bound_N)
            return true;
            else return false;

           break;
        }
        case 'd':{
            if(map[n][m+1]!='X' && m+1 < bound_M)
            return true;
            else return false;
        
            break;
        }

    }

    return false;
}

void move(char **map, int n, int m, char o, int bound_N, int bound_M){
    switch (o)
    {
        case 'w':{
            if(validator(map, n, m, o, bound_N, bound_M)){
                char aux = map[n-1][m];
                map[n-1][m] = 'K';
                map[n][m] = aux;
                n = n-1;
                break;
            }
            break;
        }
        case 'a':{
            if(validator(map, n, m, o, bound_N, bound_M)){
                char aux = map[n][m-1];
                map[n][m-1] = 'K';
                map[n][m] = aux;
                m = m-1;
                break;
            }
            break;
        }
        case 's':{
            if(validator(map, n, m, o, bound_N, bound_M)){
                char aux = map[n+1][m];
                map[n+1][m] = 'K';
                map[n][m] = aux;
                n = n+1;
                break;
            }
            break;
        }
        case 'd':{
            if(validator(map, n, m, o, bound_N, bound_M)){
                char aux = map[n][m+1];
                map[n][m+1] = 'K';
                map[n][m] = aux;
                m = m+1;
                break;
            } 
            break;
        }      
    }
}

bool game(char **map, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(map[i][j]=='F')return false;
        }
    }
    return true;
}

int findPlayerN(char **map, int n, int m){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(map[i][j]=='K')
            return i;
        }
    }

    return -1;

}

int findPlayerM(char **map, int n, int m){

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(map[i][j]=='K')
            return j;
        }
    }

    return -1;

}

int main(){

    char o;
    int n, m;



	fstream board;

	board.open("./board.txt", ios_base::in);

	if(!board.is_open()){
		cout<<"Something went wrong"<<endl;
		return 1;
	}



	char c;

	board.seekg(0);
	board.get(c);
	n = c - '0';

	board.seekg(2);
	board.get(c);
	m = c -'0';

	board.seekg(4);

    char** map;
	map = new char*[n];


	for(int i=0; i<n; i++){
		map[i] = new char[m];
	}

    for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			board >> map[i][j];
		}
	}


    print(map, n, m);
    cin>>o;
    while(game(map, n, m) == false){

        move(map, findPlayerN(map, n, m), findPlayerM(map, n, m), o, n, m);

        print(map, n, m);

        cin>>o;
    }

    
	delete[]map;

	board.close();

    return 0;
}