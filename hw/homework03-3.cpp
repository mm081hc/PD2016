#include <iostream>
using namespace std;
 
int main()
{
    int r, g, b, n, k;
	int num = 0, r1, g1, b1;  // num: number of all bad copies // r1, g1, b1: 每次輸入的r, g, b值   
    int errorR = 0, errorG = 0, errorB = 0; // errorR, errorG, errorB: error tendencies of RGB
    int num2 = 0;  // num2: number of bad copies with 2 or 3 erroneous primitive colors
    
	cin >> r >> g >> b;
    cin >> n;
    cin >> k;

    for (int i = 1; i <= n; i++)  // 當輸入的次數<=n次，繼續輸入下一個rgb值 
    {
        cin >> r1 >> g1 >> b1;
 
        if ((r1 > r + k) || (r1 < r - k) || (g1 > g + k) ||
            (g1 < g - k) || (b1 > b + k) || (b1 < b - k)) 
        {
        	int badR = 0, badG = 0, badB = 0; // badR, badG, badB: 如果輸入的r, g, b和要求的不相同，則+1 
		    num++;  // 如果輸入之RGB值超出範圍+-k，印壞數+1 
    		if (r1 > r)
    		{
				errorR++;
    			badR++;
    		}
    		if (r1 < r)
    		{
				errorR--;
    			badR++;
    		}
			if (g1 > g)
    		{
				errorG++;
    			badG++;
    		}
			if (g1 < g)
    		{
				errorG--;
    			badG++;
    		}
			if (b1 > b)
    		{
				errorB++;
    			badB++;
    		}
			if (b1 < b)
    		{
				errorB--;
    			badB++;
    		}
    		if (badR + badG + badB >= 2)  //如果r, g, b中有2個以上與要求不符，num2 + 1 
    			num2++;
		}
	}
     
    cout << errorR << " " << errorG << " " << errorB << " " << num2 << " " << num;
    
    return 0;
}
