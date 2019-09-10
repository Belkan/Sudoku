//
// Created by User on 09/09/2019.
//

#ifndef SUDOKU_GUROBI_C_H
#define SUDOKU_GUROBI_C_H
#define GRB_INT_PAR_LOGTOCONSOLE 5
#define GRB_INT_ATTR_MODELSENSE 5
#define GRB_MAXIMIZE 5
#define GRB_LESS_EQUAL 5
#define GRB_GREATER_EQUAL 5
#define GRB_INT_ATTR_STATUS 5
#define GRB_DBL_ATTR_OBJVAL 5
#define GRB_DBL_ATTR_X 5
#define GRB_OPTIMAL 5
#define GRB_INF_OR_UNBD 5
#define GRB_BINARY 'a'
typedef struct GRBenv GRBenv;
typedef struct GRBmodel GRBmodel;
int GRBloadenv(GRBenv** a, char* b);
char* GRBgeterrormsg(GRBenv* a);
int GRBsetintparam (GRBenv* a, int b, int c);
int GRBnewmodel (GRBenv* a, GRBmodel** b, char* c, int d, void* e, void* f, void* g, void* h, void* j);
int GRBaddvars(GRBmodel* a, int b, int c, void* d, void* e, void* f, double* g, void* h, void* i, char* j, void* k);
int GRBsetintattr(GRBmodel* a, int b, int c);
int GRBupdatemodel(GRBmodel* a);
int GRBaddconstr(GRBmodel* a, int b, int* c, double* d, int e, int f, char* g);
int GRBoptimize (GRBmodel* a);
int GRBwrite (GRBmodel* a, char* b);
int GRBgetintattr(GRBmodel* a, int b, int* c);
int GRBgetdblattr(GRBmodel* a, int b, double* c);
int GRBgetdblattrarray(GRBmodel* a, int b, int c, int d, double* e);
void GRBfreemodel (GRBmodel* a);
void GRBfreeenv(GRBenv* a);





#endif //SUDOKU_GUROBI_C_H
