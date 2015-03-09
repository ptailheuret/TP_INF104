int main(int argc,char* argv[]) 

{
  int n = 2;
  int premier = argv[2];

  for (premier=2;premier<n-1;premier++) 
    {
      if (n%premier==0)
	return 0;
      
      else if (premier==n)
	return 1;
    }
  return premier;
}
