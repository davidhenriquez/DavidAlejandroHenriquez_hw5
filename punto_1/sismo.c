#include<stdio.h>
#include<math.h>
#include<stdlib.h>
float tiempo(int x_obs, int y_obs, float x, float y, float v);
float probabilidad(float x, float y,int *x_obs, int *y_obs, float v, float *t, float sigma);
void metropolis(float *pos_x, float *pos_y,int *x_obs, int *y_obs, float v, float sigma, float *prob, float *t);

int main(void){
  int x_obs[6];
  int y_obs[6];
  x_obs[0] = 3;
  y_obs[0] = 15;
  x_obs[1] = 4;
  y_obs[1] = 15;
  x_obs[2] = 5;
  y_obs[2] = 15;
  x_obs[3] = 3;
  y_obs[3] = 16;
  x_obs[4] = 4;
  y_obs[4] = 16;
  x_obs[5] = 5;
  y_obs[5] = 16;
  float t[6];
  t[0] = 3.12;
  t[1] = 2.98;
  t[2] = 2.84;
  t[3] = 3.26;
  t[4] = 3.12;
  t[5] = 2.98;
  float sigma = 0.1;
  float vel = 5.0;
  int N = 100000;
  float *pos_x = malloc(N*sizeof(float));
  float *pos_y = malloc(N*sizeof(float));
  float *prob = malloc(N*sizeof(float));
  
  metropolis(pos_x,pos_y,x_obs,y_obs,vel,sigma,prob,t);

  FILE *in;
  char file[] = "sismo.dat";
  in = fopen(file,"w");
  if(!in){
    exit(1);
  }
  for(int i = 1 ;i<N; i++){
    if (*(pos_x+i) != *(pos_x+i-1)){
    fprintf(in,"%f\t %f\t %f\n",*(pos_x+i),*(pos_y+i),*(prob+i));
      }
  }
  fclose(in);

}

float tiempo(int x_obs, int y_obs, float x, float y, float v){
  return ((1.0/v)*sqrt((x_obs - x)*(x_obs - x) + (y_obs - y)*(y_obs - y)));
}

float probabilidad(float x, float y,int *x_obs, int *y_obs, float v, float *t, float sigma){
  float temp_total = 0.0;
  float temp = 0.0;
  for(int i = 0;i<6;i++){
    temp_total += tiempo(x_obs[i], y_obs[i], x, y, v);
    temp += t[i];
    }
  return exp(-(1/temp)*(temp_total-temp)*(temp_total-temp));
}

void metropolis(float *pos_x, float *pos_y, int *x_obs, int *y_obs, float v, float sigma, float *prob,float *t){
  int N = 100000;
  pos_x[0] = 5;
  pos_y[0] = 15;
  prob[0] = probabilidad(pos_x[0], pos_y[0], x_obs, y_obs, v,  t, sigma);
    for(int i = 1;i<N;i++){
      float  x_0 = ((rand() % 1001)/1000);
      float y_0 = ((rand() % 1001)/1000); 
      float p = (probabilidad(pos_x[i-1]+x_0, pos_y[i-1]+y_0, x_obs, y_obs, v,  t, sigma)/probabilidad( pos_x[i-1],  pos_y[i-1], x_obs, y_obs, v,  t, sigma));
      if(p>1){
	pos_x[i] = pos_x[i-1]+x_0;
	pos_y[i] = pos_y[i-1]+y_0;
	prob[i] = probabilidad(pos_x[i-1]+x_0, pos_y[i-1]+y_0, x_obs, y_obs, v,  t, sigma);
      }
      else{
	pos_x[i] = pos_x[i-1];
	pos_y[i] = pos_y[i-1];
	prob[i] = probabilidad(pos_x[i-1], pos_y[i-1], x_obs, y_obs, v,  t, sigma);
      
      }
    }
}
