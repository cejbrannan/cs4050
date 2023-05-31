#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct Data{
    double distance;
    struct Data* parent;
    struct Data* left;
    struct Data* right;
    int index;
}Data;

Data* after(Data* root){
    root = root->right;
    while(root->left != NULL){
        root = root->left;
    }
    return root;
}

Data* before(Data* root){
    root = root->left;
    while(root->right != NULL){
        root = root->right;
    }
    return root;
}

Data* delete(Data* root, double dist){
    if(root == NULL){
        return NULL;
    }
    if(dist > root->distance){
        root->right = delete(root->right, dist);
    }else if(dist < root->distance){
        root->left = delete(root->left, dist);
    }else{
        if(root -> left == NULL && root -> right == NULL) 
        {
            root = NULL;
        }
        else if(root -> right != NULL) 
        {
            root = after(root);
        }
        else 
        {
            root = before(root);
        }
    }
    return root;
}


Data* new(double newdist, int i){
    Data* newnode = (struct Data*)malloc(sizeof(Data));
    newnode->distance = newdist;
    newnode->parent = NULL;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->index = i;
    return newnode;
}

Data* getParent(Data* root){
    Data* parent = NULL;
    Data* temp = root;

    while(temp != NULL){
        if(temp->left == NULL || temp->right == NULL){
            parent = temp;
        }
        if(temp->left == NULL){
            break;
        }
        if(temp->right == NULL){
            temp = temp->left;
        }else{
            temp = temp->right;
        }
    }
    return parent;
}

void swap(Data* data){
    if(data->parent == NULL){
        return;
    }

    if(data->distance > data->parent->distance){
        double temp = data->distance;
        int index = data->index;
        data->distance = data->parent->distance;
        data->index = data->parent->index;
        data->parent->distance = temp;
        data->parent->index = index;
        swap(data->parent);
    }
}

void insert(Data* root[], double dist, int index){
    Data* n = new(dist, index);
    if(*root == NULL){
        *root = n;
        return;
    }
    Data* parent = getParent(*root);
    if(parent->left == NULL){
        parent->left = n;
    }else if(parent->right == NULL){
        parent->right = n;
    }else{
        parent->left->left = n;
    }
    n->parent = parent;
    swap(n);
}

void print(Data *root){
    if(root != NULL)
    {
        printf("%d - %f\n", root->index, root->distance);
        print(root->left);
        print(root->right);
    }
}

void deleteTree(Data* node)
{
    if (node == NULL) return;
 
    deleteTree(node->left);
    deleteTree(node->right);
   
    free(node);
}

double calculate(int inp[], double curr[]){
    double sum = 0;
    for(int i = 0; i < 12; i++){
        //printf("%d: %d %d", i, inp[i], curr[i]);
        double diff = inp[i] - curr[i];
        double sqr = diff * diff;
        sum += sqr;
        //printf("%d\n", sum);
    }
    
    double total = sqrt(sum);
    return total;
}

int main(int argc, char **argv)
{
    clock_t t;
    t = clock();

    if(argc < 1){
        printf("Error no arguments");
        exit(-1);
    }
    const int size = atoi(argv[1]) * 1000;
    int inp[12];
    for(int i = 0; i < 12; i++){
        inp[i] = atoi(argv[i+2]);
    }
   
    FILE* fp = fopen(argv[1], "r");
    if(!fp){
        printf("Can't open\n");
        return 0;
    }else{
        char buffer[1024];
        int row = 0;
        int column = 0;
        double array[size][12];
        while(fgets(buffer, 1024, fp)){
            column = 0;
            int arr[12];
            char* value = strtok(buffer, ",");
            while(value){
                //printf("%s ", value);
                arr[column] = atoi(value);
                value = strtok(NULL, ",");
                column++;
            }
            //for 0 to 11 add row
            for(int i = 0; i < 12; i++){
                array[row][i] = arr[i];
            }
            row++;
        }
       
        Data* root = NULL;
        for(int i = 0; i < 25; i++){
            double val = calculate(inp, array[i]);
            insert(&root, val, i+1);
        }

        for(int i = 25; i < size; i++){
            double val = calculate(inp, array[i]);
            if(val < root->distance){
                root = delete(root, root->distance);
                insert(&root, val, i+1);
            }
        }

        fclose(fp);
        
        print(root);
        deleteTree(root);
    }
    t = clock() - t;
    double totaltime = (((double)t)/CLOCKS_PER_SEC);

    printf("took %f us\n", totaltime); 
    return 0;
}
