

#include <fstream>
#include <time.h>
#include <string>
#include <sstream>
#include "CRandomGenerator.h"
#include "CPopulation.h"
#include "COptionParser.h"
#include "CStoppingCriterion.h"
#include "CEvolutionaryAlgorithm.h"
#include "global.h"
#include "CIndividual.h"

using namespace std;

#include "addPIndividual.hpp"
bool INSTEAD_EVAL_STEP = false;

CRandomGenerator* globalRandomGenerator;
extern CEvolutionaryAlgorithm* EA;
#define STD_TPL

// User declarations
#line 6 "addP.ez"
 // This section is copied on top of the output file
#include <fstream>
#include <string>
#include <iostream>
#define M_PI 3.14159265358979323846
#include <math.h>  
#include <ctype.h>
#include <cstring>
#include <sstream>
#include <cstdlib>
#include <stdio.h>
#include <float.h>

double **Nodes;
double **Transfer;
double *Ut;
double **At;
double *b;

int M=0;
int N=0;
int t=0;
int h=0;
int nodeSize=0;
int nodeDim=0;
//******************************************************
double** NodesTest;
int** TrianglesTest;
int* TrianglesSurface;
int* NodesSurface;
int nodesPoints;
int trianglesPoints;
//******************************************************
double** NodesHeart;
int** TrianglesHeart;
int* TriangleSurfaceHeart; 
int* NodesSurfaceHeart; 
int nodesPointsHeart;
int trianglesPointsHeart;
//******************************************************
double** NodesThorax;
int** TrianglesThorax; 
int* TriangleSurfaceThorax; 
int* NodesSurfaceThorax; 
int nodesPointsThorax; 
int trianglesPointsThorax;
//******************************************************
double Max;
double Min;



// User classes


// User functions

#line 58 "addP.ez"


int strtoint(std::string text) { 
	int a;
	std::stringstream stream;
	for(int b = 0; b < text.size(); b++) {
		if(!isdigit(text.at(b))) {
			text.erase(b, 1);
		}
	}
	stream<<text<<std::flush;
	stream>>a;
	return a;
}


void displayMatrix(double **mat, int rows, int cols)
{
	for (int i=0; i<rows; i++)
	{
		std::cout << i << " ";
		for (int j=0; j<cols; j++)
		{

		
			std::cout << mat[i][j] << " ";
		}
		std::cout << "" << "\n";
	}

}
void displayVector(double *vec,int size)
{
for (int j=0; j<size; j++)
		{
			std::cout << j << " ";
		
			std::cout << vec[j] << "\n";
		}
}

void readMatrix(char *name, double** &Transfer, int &M, int &N)
{
	std::ifstream file(name);
	std::string str; 
	std::getline(file, str);
	M=strtoint(str);
	std::getline(file, str);
	N=strtoint(str);
	Transfer = new double*[M];
for(int i = 0; i < M; ++i)
    Transfer[i] = new double[N];

	for (int i=0; i<M; i++)
	{
		std::getline(file, str);
		std::string word;
		std::stringstream stream(str);
		for (int j=0; j<N; j++)
		{
			std::getline(stream, word, ' ');
			Transfer[i][j]=atof(word.c_str());
			//std::istringstream os(word.c_str());
    			//os >> Transfer[i][j];
		}
	}
	std::cout << name << " Matrix loaded"<< "\n";
}

void printMatrix(double **matrix, int rows, int cols, char *name)
{
	FILE *f = fopen(name, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f, "%i\n", rows);
	fprintf(f, "%i\n", cols);

	for (int i=0;i<rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			fprintf(f, "%f ", matrix[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void printMatrixInt(int **matrix, int rows, int cols, char *name)
{
	FILE *f = fopen(name, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f, "%i\n", rows);
	fprintf(f, "%i\n", cols);

	for (int i=0;i<rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			fprintf(f, "%i ", matrix[i][j]);
		}
		fprintf(f, "\n");
	}
	fclose(f);
}

void printVectorInt(int *vec,int size, char *name)
{


FILE *f = fopen(name, "w");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}
fprintf(f, "%i\n", size);

for (int i=0;i<size;i++)
{

	fprintf(f, "%i\n", vec[i]);
}

fclose(f);



}



void readGMSH(char *name, double** &Nodes,int** &Triangles, int* &TriangleSurface, 
int* &NodesSurface, int &nodesPoints, int &trianglesPoints)
{
	std::ifstream file(name);
	std::string str;
	std::getline(file, str);//$MeshFormat
	std::getline(file, str);//2.2 0 8
	std::getline(file, str);//$EndMeshFormat
	std::getline(file, str);//$Nodes
	//
	std::getline(file, str);
	nodesPoints=strtoint(str);
	
	Nodes = new double*[nodesPoints];
	for(int i = 0; i < nodesPoints; ++i)
   		Nodes[i] = new double[3];
	
	
	for (int i=0; i<nodesPoints; i++)
	{
		std::getline(file, str);
		std::string word;
		std::stringstream stream(str);
		std::getline(stream, word, ' ');
		for (int j=0; j<3; j++)
		{
			std::getline(stream, word, ' ');
			Nodes[i][j]=atof(word.c_str());
		}
	}
	//
	std::getline(file, str);//$EndNodes
	std::getline(file, str);//$Elements
	//
	std::getline(file, str);
	trianglesPoints=strtoint(str);

	Triangles = new int*[trianglesPoints];
	for(int i = 0; i < trianglesPoints; ++i)
   		Triangles[i] = new int[3];
	
	TrianglesSurface = new int[trianglesPoints];

	for (int i=0; i<trianglesPoints; i++)
	{
		std::getline(file, str);
		std::string word;
		std::stringstream stream(str);
		std::getline(stream, word, ' ');
		std::getline(stream, word, ' ');
		std::getline(stream, word, ' ');
		std::getline(stream, word, ' ');
		std::getline(stream, word, ' ');
		TrianglesSurface[i]=strtoint(word.c_str());
		for (int j=0; j<3; j++)
		{
			std::getline(stream, word, ' ');
			Triangles[i][j]=strtoint(word.c_str());
		}
	}

	//
	NodesSurface= new int[nodesPoints];
	for (int i=0; i<trianglesPoints; i++)
	{
		for (int j=0; j<3; j++)
		{
			NodesSurface[Triangles[i][j]-1]=TrianglesSurface[i];
		}
	}
	

	std::cout << nodesPoints << " Nodes read"<< "\n";
	std::cout << trianglesPoints << " Elements read"<< "\n";
	printMatrixInt(Triangles,trianglesPoints,3,(char* ) "TriangleTest.matrix");
	printMatrix(Nodes,nodesPoints,3,(char* )"NodesTest.matrix");
	printVectorInt(TrianglesSurface,trianglesPoints,(char* )"TriangleSurfaceTest.matrix");
	printVectorInt(NodesSurface,nodesPoints,(char* )"NodesSurfaceTest.matrix");
}

void printGMSH(double **Nodes, int nodesPoints, int **Triangles, 
	int trianglesPoints, int *trianglesSurface, char *name)
{
	FILE *f = fopen(name, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f, "$MeshFormat\n");
	fprintf(f, "2.2 0 8\n");
	fprintf(f, "$EndMeshFormat\n");
	fprintf(f, "$Nodes\n");
	fprintf(f, "%i\n", nodesPoints);

	for (int i=0;i<nodesPoints;i++)
	{
		fprintf(f, "%i ", (i+1));
		for (int j=0;j<3;j++)
		{
			fprintf(f, "%f ", Nodes[i][j]);
		}
		fprintf(f, "\n");
	}
	
	
	fprintf(f, "$EndNodes\n");
	fprintf(f, "$Elements\n");
	
	fprintf(f, "%i\n", trianglesPoints);
	
	for (int i=0;i<trianglesPoints;i++)
	{
		fprintf(f, "%i ", (i+1));
		fprintf(f, "2 2 0 ");
		fprintf(f, "%i ", trianglesSurface[i]);
		for (int j=0;j<3;j++)
		{
			fprintf(f, "%i ", Triangles[i][j]);
		}
		fprintf(f, "\n");
	}
	
	fprintf(f, "$EndElements\n");
	
fclose(f);
}

void separateGMSH(double **Nodes, int nodesPoints, int **Triangles, 
	int trianglesPoints, int *NodesSurface,int *TrianglesSurface,

double** &NodesHeart,int** &TrianglesHeart, int* &TriangleSurfaceHeart, 
int* &NodesSurfaceHeart, int &nodesPointsHeart, int &trianglesPointsHeart,

double** &NodesThorax,int** &TrianglesThorax, int* &TriangleSurfaceThorax, 
int* &NodesSurfaceThorax, int &nodesPointsThorax, int &trianglesPointsThorax
)
{
	//***************************************************************************
	nodesPointsHeart=0;
	nodesPointsThorax=0;
	for (int i=0;i<nodesPoints;i++)
	{
		if(NodesSurface[i]==0)
		{
			nodesPointsHeart++;
		}
		if(NodesSurface[i]==1)
		{
			nodesPointsThorax++;
		}
	}

	NodesSurfaceHeart =  new int[nodesPointsHeart];
	NodesSurfaceThorax = new int[nodesPointsThorax];

	NodesHeart =  new double*[nodesPointsHeart];
	for(int i = 0; i < nodesPointsHeart; ++i)
   		NodesHeart[i] = new double[3];

	NodesThorax =  new double*[nodesPointsThorax];
	for(int i = 0; i < nodesPointsThorax; ++i)
   		NodesThorax[i] = new double[3];
	
	int indexH=0;
	int indexT=0;
	
	for (int i=0;i<nodesPoints;i++)
	{
		if(NodesSurface[i]==0)
		{
			for (int j=0; j<3; j++)
			{
				NodesHeart[indexH][j]=Nodes[i][j];
				
			}
			NodesSurfaceHeart[indexH]=0;
			indexH++;
		}
		if(NodesSurface[i]==1)
		{
			for (int j=0; j<3; j++)
			{
				NodesThorax[indexT][j]=Nodes[i][j];
			}
			NodesSurfaceThorax[indexT]=1;
			indexT++;
		}
	}
	//***************************************************************************Nodes
	//***************************************************************************Triangles

	trianglesPointsHeart=0;
	trianglesPointsThorax=0;
	for (int i=0;i<trianglesPoints;i++)
	{
		if(TrianglesSurface[i]==0)
		{
			trianglesPointsHeart++;
		}
		if(TrianglesSurface[i]==1)
		{
			trianglesPointsThorax++;
		}
	}
	
	TriangleSurfaceHeart=new int[trianglesPointsHeart];
	TriangleSurfaceThorax=new int[trianglesPointsThorax];

	TrianglesHeart =  new int*[trianglesPointsHeart];
	for(int i = 0; i < trianglesPointsHeart; ++i)
   		TrianglesHeart[i] = new int[3];

	TrianglesThorax =  new int*[trianglesPointsThorax];
	for(int i = 0; i < trianglesPointsThorax; ++i)
   		TrianglesThorax[i] = new int[3];

 	indexH=0;
	indexT=0;
	
	for (int i=0;i<trianglesPoints;i++)
	{
		if(TrianglesSurface[i]==0)
		{
			for (int j=0; j<3; j++)
			{
				TrianglesHeart[indexH][j]=Triangles[i][j];
			}
			TriangleSurfaceHeart[indexH]=0;
			indexH++;
		}
		if(TrianglesSurface[i]==1)
		{
			for (int j=0; j<3; j++)
			{
				TrianglesThorax[indexT][j]=Triangles[i][j]-nodesPointsHeart;
			}
			
			TriangleSurfaceThorax[indexT]=1;
			indexT++;
		}
	}
	//***************************************************************************Triangles

	printMatrix(NodesHeart,nodesPointsHeart,3,(char* )"NodesHeart.matrix");
	printMatrix(NodesThorax,nodesPointsThorax,3,(char* )"NodesThorax.matrix");

	printMatrixInt(TrianglesHeart,trianglesPointsHeart,3,(char* )"TrianglesHeart.matrix");
	printMatrixInt(TrianglesThorax,trianglesPointsThorax,3,(char* )"TrianglesThorax.matrix");

	printVectorInt(TriangleSurfaceThorax,trianglesPointsThorax,(char* )"TriangleSurfaceThorax.matrix");

	std::cout << nodesPointsHeart << " nodesPointsHeart read"<< "\n";
	std::cout << nodesPointsThorax << " nodesPointsThorax read"<< "\n";
	std::cout << trianglesPointsHeart << " trianglesPointsHeart read"<< "\n";
	std::cout << trianglesPointsThorax << " trianglesPointsThorax read"<< "\n";

	printGMSH(NodesHeart, nodesPointsHeart, TrianglesHeart, 
	trianglesPointsHeart, TriangleSurfaceHeart,(char* ) "heart.msh");
	
	printGMSH(NodesThorax, nodesPointsThorax, TrianglesThorax, 
	trianglesPointsThorax, TriangleSurfaceThorax,(char* ) "thorax.msh");
}

double**  GenerateNodesRGB(double* Load, double** NodesTest, double Max2, double Min2,int nodesPointsRGB)
        {
            double** NodesRGB = 
		NodesRGB =  new double*[nodesPointsRGB];
		for(int i = 0; i < nodesPointsRGB; i++)
   		NodesRGB[i] = new double[3];

            double min = Min2;
            double max = Max2;

            for (int i = 0; i < nodesPointsRGB; i++)
            {
                double x = (Load[i] - min) / (max - min);
                double R = 0;
                double G = 0;
                double B = 0;



                if (x <= 0.33)
                {
                    B = 1;
                    G = x / 0.33;
                    R = 0;

                }
                if (x <= 0.50 && x > 0.33)
                {
                    double diferencia = (x - 0.33) / 0.17;
                    B = 1 - diferencia;
                    G = 1;
                    R = 0;
                }
                //
                if (x <= 0.66 && x > 0.50)
                {
                    double diferencia = (x - 0.50) / 0.16;
                    B = 0;
                    G = 1;
                    R = diferencia;
                }
                if (x <= 1.00 && x > 0.66)
                {
                    double diferencia = (x - 0.66) / 0.33;
                    B = 0;
                    G = 1-diferencia;
                    R = 1;
                }

                NodesRGB[i][ 0] = R/1.5;
                NodesRGB[i][ 1] = G/1.5;
                NodesRGB[i][ 2] = B/1.5;



            }

            return NodesRGB;
        }

void createJS(double** NodesRGB,int** TrianglesRGB,int trianglesPointsRGB, char *name)
{
	FILE *f = fopen(name, "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}

	//TextWriter tw = new StreamWriter(".\\var\\"+k.ToString() + ".js");
                double** matrix = NodesRGB;
                fprintf(f,"var colorCodes = new Array(\n");


                for (int i = 0; i < trianglesPointsRGB; i++)
                {
                    for (int j = 0; j < 3; j++)
                    {
                        int node = TrianglesRGB[i][j]-1;
   			
			fprintf(f,"new Array(");
                        fprintf(f,"%f,",matrix[node][ 0]);
                        fprintf(f,"%f,",matrix[node][ 1]);
                        if (i == trianglesPointsRGB - 1 && j == 2)
                        {
                           	//fprintf(f,"x");
				fprintf(f,"%f)",matrix[node][2]);			
                        }
                        else
                        {
                    		//fprintf(f,"x");
				fprintf(f,"%f),",matrix[node][1]);
                        }
                        fprintf(f,"\n");
                    }
                }
                fprintf(f,")");
                fprintf(f,"\n");



fclose(f);


}

void readVector(char *name, double* &Ut,int &t)
{
	std::ifstream file(name);
	std::string str; 
	std::getline(file, str);
	t=strtoint(str);
	Ut = new double[t];
	for (int i=0; i<t; i++)
	{
		std::getline(file, str);
		std::string word;
		std::stringstream stream(str);
		std::getline(stream, word, ' ');
		Ut[i]=atof(word.c_str());

	}
std::cout << name<<" Vector loaded"<< std::endl;	
}

void printVector(double *vec,int size, char *name)
{


FILE *f = fopen(name, "w");
if (f == NULL)
{
    printf("Error opening file!\n");
    exit(1);
}
fprintf(f, "%i\n", size);

for (int i=0;i<size;i++)
{

	fprintf(f, "%f\n", vec[i]);
}

fclose(f);



}


double* Mult(double **matrix0, double *vector0, int rows, int cols)
{

    double *outputvector = new double[rows];
	
    for (int i = 0; i < rows; i++)
    {
	outputvector[i]=0.0;

        for (int j = 0; j < cols; j++)
        {

            outputvector[i] += matrix0[i][j] * vector0[j];
	    
        }

    }

    return outputvector;
}

double getCost(double a,double b, double c)
{

double* Uh=new double[h];
	   for (int i = 0; i < h; i++ )
	   {
	    	double x=(Nodes[i][0]-a);
		double y=(Nodes[i][1]-b);
		double z=(Nodes[i][2]-c);

		Uh[i]=1.0/(4.0*M_PI*sqrt(x*x+y*y+z*z));
	   }

	double *Uttemp=Mult(Transfer,Uh,M,N);

	double temp=0.0;
	for (int i = 0; i < t; i++ )
	   {
	    	temp+=abs(Ut[i]-Uttemp[i]);
	   }

free(Uh);
free(Uttemp);
  return temp;
}

double getCost2(double a,double b, double c, double d)
{

double* Uh=new double[h];
	   for (int i = 0; i < h; i++ )
	   {
	    	double x=(Nodes[i][0]-a);
		double y=(Nodes[i][1]-b);
		double z=(Nodes[i][2]-c);

		Uh[i]=1.0/(4.0*M_PI*sqrt(x*x+y*y+z*z))+d;
	   }

	double *Uttemp=Mult(Transfer,Uh,M,N);

	double temp=0.0;
	for (int i = 0; i < t; i++ )
	   {
	    	temp+=abs(Ut[i]-Uttemp[i]);
	   }

free(Uh);
free(Uttemp);
  return temp;
}



double Dot(double *vector1, double *vector2, int size)
  {
    double sum = 0.0;
    double vectorDotProductOut = 0.0;
	for (int i = 0; i < size; i++ )

	{
      		sum += vector1[i] * vector2[i];
    	}
    vectorDotProductOut = sum;
return vectorDotProductOut;
  }

double* MultC(double *vector, int size, double c)
  {
    double *outputvector = new double[size];
	for (int i = 0; i < size; i++ )

	{
      		outputvector[i]=vector[i]*c;
    	}

return outputvector;
  }

double* Add(double *vector1, double *vector2, int size)
  {
    double *outputvector = new double[size];

	for (int i = 0; i < size; i++ )

	{
      		outputvector[i]= vector1[i] + vector2[i];
    	}

return outputvector;
  }

double* Sub(double *vector1, double *vector2, int size)
  {
    double *outputvector = new double[size];

	for (int i = 0; i < size; i++ )

	{
      		outputvector[i]= vector1[i] - vector2[i];
    	}

return outputvector;
  }

double** Tvector(double* vector,int size)
{

	double** TransVector= new double*[1];
	for(int i = 0; i < 1; ++i)
    		TransVector[i] = new double[size];

	for (int i = 0; i < size; i++ )

	{
      		TransVector[0][i]= vector[i];
		
    	}
	return TransVector;
}


        double** MultM(double** Matrix1, double** Matrix2, int rowsMatrix1, int colsMatrix1,int rowsMatrix2,int colsMatrix2)
        {
            //double** matrixdouble = new double[Matrix1.GetLength(0), Matrix2.GetLength(1)];
		double** matrixdouble= new double*[rowsMatrix1];
	for(int i = 0; i < rowsMatrix1; ++i)
    		matrixdouble[i] = new double[colsMatrix2];

            for (int i = 0; i < rowsMatrix1; i++)
            {
                for (int j = 0; j < colsMatrix2; j++)
                {
                    double suma = 0;
                    for (int k = 0; k < colsMatrix1; k++)
                    {
                        suma += Matrix1[i][ k] * Matrix2[k][ j];
                    }
                    matrixdouble[i][ j] = suma;
                }
            }
            return matrixdouble;
        }

 double** MT(double** matrix, int rowsMatrix1, int colsMatrix1)
        {
            //double[,] matrixout = new double[matrix.GetLength(1), matrix.GetLength(0)];

double** matrixout= new double*[colsMatrix1];
	for(int i = 0; i < colsMatrix1; ++i)
    		matrixout[i] = new double[rowsMatrix1];

            for (int i = 0; i < colsMatrix1; i++)
            {
                for (int j = 0; j < rowsMatrix1; j++)
                {
                    matrixout[i][j] = matrix[j][i];
                }

            }
            return matrixout;
        }

double* CG(double **A,double* b, double* x0,int rowsA,int colsA)
{	
	double* x=new double[colsA];
	//r=b-A*x;
	double* Ax=Mult(A,x,rowsA,colsA);
	double* r=Sub(Ax,b,rowsA);
	double* p=r;
	//rsold=r'*r;
	double rsold=Dot(r,r,rowsA);
    	
 
	//for i=1:1e6
	int iter=0;
	double res=1e6;
	while (iter <1000 && res>1e-10)
	{
		//Ap=A*p;
		double* Ap=Mult(A,p,rowsA,colsA);
		//alpha=rsold/(p'*Ap);
		double	pAp=Dot(p,Ap,rowsA);
		double	alpha=rsold/pAp;
		//x=x+alpha*p;
		double* alphap=MultC(p,rowsA,alpha);
		x=Add(x,alphap,rowsA);
		//r=r-alpha*Ap;
        	double* alphaAp=MultC(Ap,rowsA,alpha);
		r=Sub(r,alphaAp,rowsA);
		//rsnew=r'*r;
		double	rsnew=Dot(r,r,colsA);
		//if sqrt(rsnew)<1e-10
        	//      break;
        	//end
        	res=sqrt(rsnew);
        	iter=iter+1;
		//p=r+rsnew/rsold*p;
        	double	beta=rsnew/rsold;
		double*	betap=MultC(p,rowsA,beta);
		p=Add(r,betap,rowsA);
        	//rsold=rsnew
		rsold=rsnew;
		
		//displayVector(x,rowsA);
	}	
	cout<<iter<<endl;
	return x;
}





// Initialisation function
void EASEAInitFunction(int argc, char *argv[]){
#line 845 "addP.ez"

{
	readGMSH(const_cast<char *>("ht.msh"),NodesTest,
		TrianglesTest,TrianglesSurface,NodesSurface,
		nodesPoints,trianglesPoints);
	
separateGMSH(NodesTest, nodesPoints, TrianglesTest, 
	trianglesPoints, NodesSurface,TrianglesSurface,

NodesHeart,TrianglesHeart, TriangleSurfaceHeart, 
NodesSurfaceHeart, nodesPointsHeart, trianglesPointsHeart,

NodesThorax,TrianglesThorax, TriangleSurfaceThorax, 
NodesSurfaceThorax, nodesPointsThorax, trianglesPointsThorax
);
	printGMSH(NodesTest, nodesPoints, TrianglesTest, 
	trianglesPoints, TrianglesSurface,(char* ) "test.msh");
	//exit(1);
	//double Max=DBL_MAX;
	//double Min=DBL_MAX*-1;


	readMatrix(const_cast<char *>("Transfer.matrix"),Transfer,M,N);
	readVector(const_cast<char *>("Ut.txt"),Ut,t);
	readMatrix(const_cast<char *>("NodesHeart.matrix"),Nodes,nodeSize,nodeDim);
	cout<<M<<endl;
	cout<<N<<endl;
	cout<<nodeSize<<endl;
	cout<<nodeDim<<endl;
	At=MT(Transfer,  M,  N);
	cout<<"At ready"<<endl;
	double** A=MultM(At, Transfer, N, M,M,N);
	cout<<"A ready"<<endl;
	printMatrix(A,N,N,(char* )"A");

	double* b=Mult(At,Ut,N,M);
	cout<<"b ready"<<endl;

	
	double* x0=new double[N];
	double* x =CG(A,b, x0,M,M);
	double* ut2=Mult(Transfer,x,M,N);
	printVector(x,N,(char* )"x");
	printVector(ut2,M,(char* )"ut2");
	h=N;

	Max=x[0];
	Min=x[0];
	for (int i=0;i<h;i++)
	{
		if (x[i]>Max)
		{
			Max=x[i];
		}
		if (x[i]<Min)
		{
			Min=x[i];
		}
	}
	
	//cout<<h<<endl;
	//cout<<nodesPointsHeart<<endl;
	cout<<Max<<endl;
	cout<<Min<<endl;
	double** NodesRGB=GenerateNodesRGB(x, NodesHeart,  Max,  Min,nodesPointsHeart);
	printMatrix(NodesRGB,h,3,(char* )"NodesRGB.matrix");
	//cout<<trianglesPointsHeart<<endl;
	//".\\var\\"+k.ToString() + ".js"
	createJS(NodesRGB,TrianglesHeart,trianglesPointsHeart, (char* )"./geometries/var/0.js");

	//exit(1);
}
}

// Finalization function
void EASEAFinalization(CPopulation* population){
#line 919 "addP.ez"


//std::cout << (*population) ;

cout <<(population->Best->serialize())<<endl;
string str=population->Best->serialize();

	string word;
	stringstream stream(str);

		getline(stream, word, ' ');
		double d=atof(word.c_str());
		getline(stream, word, ' ');
		double c=atof(word.c_str());
		getline(stream, word, ' ');
		double b=atof(word.c_str());
		getline(stream, word, ' ');
		double a=atof(word.c_str());


cout << a << "\n";
cout << b << "\n";
cout << c << "\n";
cout << d << "\n";

double cost=getCost2(a,b,c,d);
cout<<cost<<endl;
double* Uh=new double[h];
	   for (int i = 0; i < h; i++ )
	   {
	    	double x=(Nodes[i][0]-a);
		double y=(Nodes[i][1]-b);
		double z=(Nodes[i][2]-c);

		Uh[i]=1.0/(4.0*M_PI*sqrt(x*x+y*y+z*z))+d;
	   }

	double *Uttemp=Mult(Transfer,Uh,M,N);

	double temp=0.0;
	for (int i = 0; i < t; i++ )
	   {
	    	temp+=abs(Ut[i]-Uttemp[i]);
	   }
printVector(Uttemp,t,(char* )"Uttemp");
printVector(Uh,h  ,(char* )"Uh");

	double** NodesRGB=GenerateNodesRGB(Uh, NodesHeart,  Max,  Min,nodesPointsHeart);
	printMatrix(NodesRGB,h,3,(char* )"NodesRGB2.matrix");
	//cout<<trianglesPointsHeart<<endl;
	//".\\var\\"+k.ToString() + ".js"
	createJS(NodesRGB,TrianglesHeart,trianglesPointsHeart, (char* )"./geometries/var/1.js");

}



void evale_pop_chunk(CIndividual** population, int popSize){
  
// No Instead evaluation step function.

}

void addPInit(int argc, char** argv){
	
  EASEAInitFunction(argc, argv);

}

void addPFinal(CPopulation* pop){
	
  EASEAFinalization(pop);
;
}

void EASEABeginningGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	#line 1229 "addP.ez"
{
#line 974 "addP.ez"
{
}
}
}

void EASEAEndGenerationFunction(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{


}
}

void EASEAGenerationFunctionBeforeReplacement(CEvolutionaryAlgorithm* evolutionaryAlgorithm){
	{

  //cout << "At each generation before replacement function called" << endl;

}
}


IndividualImpl::IndividualImpl() : CIndividual() {
   
  // Genome Initialiser
#line 1000 "addP.ez"
 // "initializer" is also accepted
  // the genome to initialise is known as "(*this)"
 (*this).a=globalRandomGenerator->random(-100.0,100.0);
 (*this).b=globalRandomGenerator->random(-100.0,100.0);
 (*this).c=globalRandomGenerator->random(-100.0,100.0);
 (*this).d=globalRandomGenerator->random(-100.0,100.0);

  valid = false;
  isImmigrant = false;
}

CIndividual* IndividualImpl::clone(){
	return new IndividualImpl(*this);
}

IndividualImpl::~IndividualImpl(){
  // Destructing pointers

}


float IndividualImpl::evaluate(){
  if(valid)
    return fitness;
  else{
    valid = true;
    #line 1185 "addP.ez"
 // Returns the score as a real value
 	//IndividualImpl::printOn(std::cout); 

	double temp=getCost2((*this).a,(*this).b,(*this).c, (*this).d);

  return fitness =  temp;

  }
}

void IndividualImpl::boundChecking(){
	
// No Bound checking function.
}

string IndividualImpl::serialize(){
    ostringstream EASEA_Line(ios_base::app);
    // Memberwise serialization
	EASEA_Line << this->d << " ";
	EASEA_Line << this->c << " ";
	EASEA_Line << this->b << " ";
	EASEA_Line << this->a << " ";

    EASEA_Line << this->fitness;
    return EASEA_Line.str();
}

void IndividualImpl::deserialize(string Line){
    istringstream EASEA_Line(Line);
    string line;
    // Memberwise deserialization
	EASEA_Line >> this->d;
	EASEA_Line >> this->c;
	EASEA_Line >> this->b;
	EASEA_Line >> this->a;

    EASEA_Line >> this->fitness;
    this->valid=true;
    this->isImmigrant = false;
}

IndividualImpl::IndividualImpl(const IndividualImpl& genome){

  // ********************
  // Problem specific part
  // Memberwise copy
    d=genome.d;
    c=genome.c;
    b=genome.b;
    a=genome.a;



  // ********************
  // Generic part
  this->valid = genome.valid;
  this->fitness = genome.fitness;
  this->isImmigrant = false;
}


CIndividual* IndividualImpl::crossover(CIndividual** ps){
	// ********************
	// Generic part
	IndividualImpl** tmp = (IndividualImpl**)ps;
	IndividualImpl parent1(*this);
	IndividualImpl parent2(*tmp[0]);
	IndividualImpl child(*this);

	//DEBUG_PRT("Xover");
	/*   cout << "p1 : " << parent1 << endl; */
	/*   cout << "p2 : " << parent2 << endl; */

	// ********************
	// Problem specific part
  	#line 1008 "addP.ez"
 

double cost=getCost2(parent1.a,parent1.b,parent1.c,parent1.d);
child.a=parent1.a;
child.b=parent1.b;
child.c=parent1.c;
child.d=parent1.d;

double costTemp=getCost2(parent1.a,parent1.b,parent2.c,parent1.d);
if (costTemp<=cost)
{
child.a=parent1.a;
child.b=parent1.b;
child.c=parent2.c;
child.d=parent1.d;
cost=costTemp;
}

costTemp=getCost2(parent1.a,parent2.b,parent1.c,parent1.d);
if (costTemp<=cost)
{
child.a=parent1.a;
child.b=parent2.b;
child.c=parent1.c;
child.d=parent1.d;
cost=costTemp;
}

costTemp=getCost2(parent1.a,parent2.b,parent2.c,parent1.d);
if (costTemp<=cost)
{
child.a=parent1.a;
child.b=parent2.b;
child.c=parent2.c;
child.d=parent1.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent1.b,parent1.c,parent1.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent1.b;
child.c=parent1.c;
child.d=parent1.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent1.b,parent2.c,parent1.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent1.b;
child.c=parent2.c;
child.d=parent1.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent2.b,parent1.c,parent1.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent2.b;
child.c=parent1.c;
child.d=parent1.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent2.b,parent2.c,parent1.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent2.b;
child.c=parent2.c;
child.d=parent1.d;
cost=costTemp;
}

//second batch
costTemp=getCost2(parent1.a,parent1.b,parent1.c,parent2.d);
child.a=parent1.a;
child.b=parent1.b;
child.c=parent1.c;
child.d=parent2.d;

costTemp=getCost2(parent1.a,parent1.b,parent2.c,parent2.d);
if (costTemp<=cost)
{
child.a=parent1.a;
child.b=parent1.b;
child.c=parent2.c;
child.d=parent2.d;
cost=costTemp;
}

costTemp=getCost2(parent1.a,parent2.b,parent1.c,parent2.d);
if (costTemp<=cost)
{
child.a=parent1.a;
child.b=parent2.b;
child.c=parent1.c;
child.d=parent2.d;
cost=costTemp;
}

costTemp=getCost2(parent1.a,parent2.b,parent2.c,parent2.d);
if (costTemp<=cost)
{
child.a=parent1.a;
child.b=parent2.b;
child.c=parent2.c;
child.d=parent2.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent1.b,parent1.c,parent2.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent1.b;
child.c=parent1.c;
child.d=parent2.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent1.b,parent2.c,parent2.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent1.b;
child.c=parent2.c;
child.d=parent2.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent2.b,parent1.c,parent2.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent2.b;
child.c=parent1.c;
child.d=parent2.d;
cost=costTemp;
}

costTemp=getCost2(parent2.a,parent2.b,parent2.c,parent2.d);
if (costTemp<=cost)
{
child.a=parent2.a;
child.b=parent2.b;
child.c=parent2.c;
child.d=parent2.d;
cost=costTemp;
}




	child.valid = false;
	/*   cout << "child : " << child << endl; */
	return new IndividualImpl(child);
}


void IndividualImpl::printOn(std::ostream& os) const{
	
	printf("%f %f %f %f\n",(*this).a, (*this).b, (*this).c, (*this).d);
//printf("0.000000 \n",Genome.a);

}

std::ostream& operator << (std::ostream& O, const IndividualImpl& B)
{
  // ********************
  // Problem specific part
  O << "\nIndividualImpl : "<< std::endl;
  O << "\t\t\t";
  B.printOn(O);

  if( B.valid ) O << "\t\t\tfitness : " << B.fitness;
  else O << "fitness is not yet computed" << std::endl;
  return O;
}


unsigned IndividualImpl::mutate( float pMutationPerGene ){
  this->valid=false;


  // ********************
  // Problem specific part
  #line 1165 "addP.ez"
 // Must return the number of mutations
   if (globalRandomGenerator->tossCoin(0.4)){
     (*this).a+=globalRandomGenerator->random(-1.0,1.0);
     return  1>0?true:false;
   }
   if (globalRandomGenerator->tossCoin(0.4)){
     (*this).b+=globalRandomGenerator->random(-1.0,1.0);
     return  1>0?true:false;
   }
   if (globalRandomGenerator->tossCoin(0.4)){
     (*this).c+=globalRandomGenerator->random(-1.0,1.0);
     return  1>0?true:false;
   }
if (globalRandomGenerator->tossCoin(0.4)){
     (*this).d+=globalRandomGenerator->random(-0.1,0.1);
     return  1>0?true:false;
   }
  return  0 >0?true:false;

}

void ParametersImpl::setDefaultParameters(int argc, char** argv){

	this->minimizing = true;
	this->nbGen = setVariable("nbGen",(int)100);

	seed = setVariable("seed",(int)time(0));
	globalRandomGenerator = new CRandomGenerator(seed);
	this->randomGenerator = globalRandomGenerator;


	selectionOperator = getSelectionOperator(setVariable("selectionOperator","Tournament"), this->minimizing, globalRandomGenerator);
	replacementOperator = getSelectionOperator(setVariable("reduceFinalOperator","Tournament"),this->minimizing, globalRandomGenerator);
	parentReductionOperator = getSelectionOperator(setVariable("reduceParentsOperator","Tournament"),this->minimizing, globalRandomGenerator);
	offspringReductionOperator = getSelectionOperator(setVariable("reduceOffspringOperator","Tournament"),this->minimizing, globalRandomGenerator);
	selectionPressure = setVariable("selectionPressure",(float)20.000000);
	replacementPressure = setVariable("reduceFinalPressure",(float)7.000000);
	parentReductionPressure = setVariable("reduceParentsPressure",(float)10.000000);
	offspringReductionPressure = setVariable("reduceOffspringPressure",(float)10.000000);
	pCrossover = 1.000000;
	pMutation = 1.000000;
	pMutationPerGene = 0.05;

	parentPopulationSize = setVariable("popSize",(int)100);
	offspringPopulationSize = setVariable("nbOffspring",(int)50);


	parentReductionSize = setReductionSizes(parentPopulationSize, setVariable("survivingParents",(float)50.000000));
	offspringReductionSize = setReductionSizes(offspringPopulationSize, setVariable("survivingOffspring",(float)50.000000));

	this->elitSize = setVariable("elite",(int)1);
	this->strongElitism = setVariable("eliteType",(int)1);

	if((this->parentReductionSize + this->offspringReductionSize) < this->parentPopulationSize){
		printf("*WARNING* parentReductionSize + offspringReductionSize < parentPopulationSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if((this->parentPopulationSize-this->parentReductionSize)>this->parentPopulationSize-this->elitSize){
		printf("*WARNING* parentPopulationSize - parentReductionSize > parentPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	if(!this->strongElitism && ((this->offspringPopulationSize - this->offspringReductionSize)>this->offspringPopulationSize-this->elitSize)){
		printf("*WARNING* offspringPopulationSize - offspringReductionSize > offspringPopulationSize - elitSize\n");
		printf("*WARNING* change Sizes in .prm or .ez\n");
		printf("EXITING\n");
		exit(1);	
	} 
	

	/*
	 * The reduction is set to true if reductionSize (parent or offspring) is set to a size less than the
	 * populationSize. The reduction size is set to populationSize by default
	 */
	if(offspringReductionSize<offspringPopulationSize) offspringReduction = true;
	else offspringReduction = false;

	if(parentReductionSize<parentPopulationSize) parentReduction = true;
	else parentReduction = false;

	generationalCriterion = new CGenerationalCriterion(setVariable("nbGen",(int)100));
	controlCStopingCriterion = new CControlCStopingCriterion();
	timeCriterion = new CTimeCriterion(setVariable("timeLimit",0));

	this->optimise = 0;

	this->printStats = setVariable("printStats",1);
	this->generateCSVFile = setVariable("generateCSVFile",1);
	this->generatePlotScript = setVariable("generatePlotScript",0);
	this->generateRScript = setVariable("generateRScript",0);
	this->plotStats = setVariable("plotStats",0);
	this->printInitialPopulation = setVariable("printInitialPopulation",0);
	this->printFinalPopulation = setVariable("printFinalPopulation",0);
	this->savePopulation = setVariable("savePopulation",1);
	this->startFromFile = setVariable("startFromFile",0);

	this->outputFilename = (char*)"addP";
	this->plotOutputFilename = (char*)"addP.png";

	this->remoteIslandModel = setVariable("remoteIslandModel",0);
	std::string* ipFilename=new std::string();
	*ipFilename=setVariable("ipFile","ip.txt");

	this->ipFile =(char*)ipFilename->c_str();
	this->migrationProbability = setVariable("migrationProbability",(float)0.330000);
    this->serverPort = setVariable("serverPort",2929);
}

CEvolutionaryAlgorithm* ParametersImpl::newEvolutionaryAlgorithm(){

	pEZ_MUT_PROB = &pMutationPerGene;
	pEZ_XOVER_PROB = &pCrossover;
	//EZ_NB_GEN = (unsigned*)setVariable("nbGen",100);
	EZ_current_generation=0;
  EZ_POP_SIZE = parentPopulationSize;
  OFFSPRING_SIZE = offspringPopulationSize;

	CEvolutionaryAlgorithm* ea = new EvolutionaryAlgorithmImpl(this);
	generationalCriterion->setCounterEa(ea->getCurrentGenerationPtr());
	ea->addStoppingCriterion(generationalCriterion);
	ea->addStoppingCriterion(controlCStopingCriterion);
	ea->addStoppingCriterion(timeCriterion);	

	EZ_NB_GEN=((CGenerationalCriterion*)ea->stoppingCriteria[0])->getGenerationalLimit();
	EZ_current_generation=&(ea->currentGeneration);

	 return ea;
}

void EvolutionaryAlgorithmImpl::initializeParentPopulation(){
	if(this->params->startFromFile){
	  ifstream EASEA_File("addP.pop");
	  string EASEA_Line;
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
	  	  getline(EASEA_File, EASEA_Line);
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
		  ((IndividualImpl*)this->population->parents[i])->deserialize(EASEA_Line);
	  }
	  
	}
	else{
  	  for( unsigned int i=0 ; i< this->params->parentPopulationSize ; i++){
		  this->population->addIndividualParentPopulation(new IndividualImpl(),i);
	  }
	}
        this->population->actualParentPopulationSize = this->params->parentPopulationSize;
}


EvolutionaryAlgorithmImpl::EvolutionaryAlgorithmImpl(Parameters* params) : CEvolutionaryAlgorithm(params){
	;
}

EvolutionaryAlgorithmImpl::~EvolutionaryAlgorithmImpl(){

}

