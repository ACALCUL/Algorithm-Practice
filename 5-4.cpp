#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> matrix_t;
matrix_t path;



int solve(int row, int col, matrix_t tri, matrix_t& cost){
    if(row==tri.size()){
        return 0;
    }
    else if(cost[row][col]==0){
        int submax, left, right;
        left=solve(row+1,col,tri,cost);
        right=solve(row+1, col+1, tri,cost);
        if(left > right){
            submax=left;
            path[row][col]=0;
        }
        else{//left와 right가 같거나 right가 더 클 때
            submax=right;
            path[row][col]=1;
        }
        cost[row][col]= tri[row][col] + submax;
    }

    return cost[row][col];
}

void print_path(matrix_t tri){
    int row=0; 
    int col=0;
    cout << tri[row][col];
    while(row<tri.size()-1){
        if(path[row][col]==0){
            row++;
        }
        else{
            row++;
            col++;
        }
        cout << " "<<tri[row][col];
    }

}


int main(){
    int h;
    cin >> h;

    matrix_t tri(h, vector<int>(h,0));
    path.resize(h, vector<int>(h,0));
    int n;
    for(int i=0; i<h; i++){
        for(int j=0; j<=i; j++){
            cin >> n;
            tri[i][j]=n;
        }
    }
    /* for(int i=0; i<h; i++){
        for(int j=0; j<h; j++){
            cout << tri[i][j] << " ";
        }
        cout << endl;
    } */
    matrix_t cost(h, vector<int>(h,0));

    cout << solve(0, 0, tri, cost)<<endl;

    /* for(int i=0; i<h; i++){
        for(int j=0; j<h; j++){
            cout << path[i][j] << " ";
        }
        cout << endl;
    }  */
    print_path(tri);

    return 0;
}