#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
float probabilidad_x(float a,float b,float *x,float *y,float *t);
float probabilidad_y(float c,float d,float *x,float *y,float *t);

int main(void){
  int N = 100000;
  float x[96];
  float y[96];
  float t[96];
  char str[98];
  float a[N];
  a[0] = 1;
  float b[N];
  b[0] = 1;
  float c[N];
  c[0] = 1;
  float d[N];
  d[0] = 1;
  float delta_a = 0.01;
  float delta_b = 0.01;
  float delta_c = 0.01;
  float delta_d = 0.01;

  
  FILE *in;
  in = fopen("lotka_volterra_obs.dat", "r");
  fscanf(in, "%*[^\n]\n", NULL);
  fscanf(in, "%*[^\n]\n", NULL);
  
  float arr[96*3];
  int l;

  for (l = 0; l < 96*3; l++)
    {
      fscanf(in, "%f", &arr[l]);
    }
  
 
  int i;
  for(i = 0;i<96;i++){
    t[i] = arr[i*3];
    x[i] = arr[i*3+1];
    y[i] = arr[i*3+2];
  }

  int j;
  for(j=1;j<N;j++){
    float a_new = a[j-1] + delta_a*(((rand() % 1001)/1000) - 0.5)*2;
    float b_new = b[j-1] + delta_b*(((rand() % 1001)/1000) - 0.5)*2;
    
    float p_new = probabilidad_x(a_new,b_new,x,y,t);
    float p_old = probabilidad_x(a[i-1],b[i-1],x,y,t);
    
    float alpha_x = 0;
    if ((p_new/p_old) < 1){
      alpha_x = p_new/p_old; 
    }
    else{
      alpha_x = 1;
    }

    float r = ((rand() % 1001)/1000);
    if (r<alpha_x){
      a[j] = a_new;
      b[j] = b_new;
    }
    else{
      a[j] = a[j-1];
      b[j] = b[j-1];
    }
  
  }

  int k;
  for(k=1;k<N;k++){
    float c_new = c[k-1] + delta_c*(((rand() % 1001)/1000) - 0.5)*2;
    float d_new = d[k-1] + delta_d*(((rand() % 1001)/1000) - 0.5)*2;

    float p_new = probabilidad_y(c_new,d_new,x,y,t);
    float p_old = probabilidad_y(c[i-1],d[i-1],x,y,t);
    
    float alpha_y = 0;
    if ((p_new/p_old) < 1){
      alpha_y = p_new/p_old;
    }
    else{
      alpha_y = 1;
    }

    float r = ((rand() % 1001)/1000);
    if (r<alpha_y){
      c[k] = c_new;
      d[k] = d_new;
    }
    else{
      c[k] = c[k-1];
      d[k] = d[k-1];
    }

  }


  FILE *in1;
  char file1[] = "a.dat";
  in1 = fopen(file1,"w");
  if(!in1){
    exit(1);
  }
  for(int i = 0 ;i<N; i++){
    fprintf(in1,"%f\n",*(a+i));
  }
  fclose(in1);
    
  FILE *in2;
  char file2[] = "b.dat";
  in2 = fopen(file2,"w");
  if(!in2){
    exit(1);
  }
  for(int i = 0 ;i<N; i++){
    fprintf(in2,"%f\n",*(b+i));
  }
  fclose(in2);
  
  FILE *in3;
  char file3[] = "c.dat";
  in3 = fopen(file3,"w");
  if(!in3){
    exit(1);
  }
  for(int i = 0 ;i<N; i++){
    fprintf(in3,"%f\n",*(c+i));
  }
  fclose(in3);
  

  FILE *in4;
  char file4[] = "d.dat";
  in4 = fopen(file4,"w");
  if(!in4){
    exit(1);
  }
  for(int i = 0 ;i<N; i++){
    fprintf(in4,"%f\n",*(d+i));
  }
  fclose(in4);

  return 0;
}

float probabilidad_x(float a,float b,float *x,float *y,float *t){
  int i;
  float x_obs = 0.0;
  for(i = 1;i<95;i++){
    x_obs += pow(x[i-1]*(1+(t[i]-t[i-1])*(a-b*y[i])) - x[i-1],2)*(1.0/2);
  }
  float p_obs = exp(-x_obs);
  return p_obs;
}

float probabilidad_y(float c,float d,float *x,float *y,float *t){
  int i;
  float y_obs = 0.0;
  for(i = 1;i<95;i++){
    y_obs += pow(y[i-1]*(1-(t[i]-t[i-1])*(c-d*x[i])) - y[i-1],2)*(1.0/2);
  }
  float p_obs = exp(-y_obs);
  return p_obs;
}

