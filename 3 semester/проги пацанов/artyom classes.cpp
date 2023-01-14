#include <iostream>
#include <algorithm>
#include <cmath>
#include <ostream>
#include <vector>
#include <string>
using namespace std;

class Decimal
{
    private:
        string sgn;
        int int_size;
	    int accuracy;
	    int *number;
        int *fraction;
        static int size(int a)
        {
            a=fabs(a);
            int k=0;
            while(a>0)
            {
                a/=10;
                k++;
            }
            return k;
        }
    public: //______________________CONSTRUCTORS_________________________________________________
    Decimal():
        sgn("+"),
        int_size(1),
        accuracy(0),
        number(new int[1]),
        fraction(nullptr)
    {
        number[0]=0;
        //fraction[0]=1;
    }
    Decimal(const Decimal& other):
        sgn(other.sgn),
        int_size(other.int_size),
        accuracy(other.accuracy),
        number(new int[int_size]),
        fraction(new int[accuracy] )
    {
        for (int i=0; i< accuracy; i++)
            fraction[i]=other.fraction[i];
        for(int i=0; i<int_size; i++)
            number[i]=other.number[i];
    }
    Decimal(int other):
        sgn("+"),
        int_size(size(other)),
        accuracy(0),
        number(new int[int_size]),
        fraction(nullptr)
    {
            if (other<0)
            {
                sgn="-";
                other*=-1;
            }
            for (int i=0; i<int_size; i++)
            {
                number[i]=other%10;
                other/=10;
            }
    }
    Decimal(double other):
        sgn("+"),
        int_size(size((int)other)),
        //int_size(2),
        accuracy(20),
        number(new int[int_size]),
        fraction(new int[accuracy])
        {
            //cout<<"int_size"<<int_size<<endl;
            if (other<0)
            {
                sgn="-";
                other*=-1;
            }
            int tmp=(int)other;
            for (int i=0; i<int_size; i++)
            {
                number[i]=tmp%10;
                tmp/=10;
                //cout<<" number["<<i<<"]="<<number[i];
            }
            cout<<endl;
            //cout
            //other=fabs(other);
            other=((other-trunc(other))*10);
            for (int i=0; i<accuracy; i++)
            {
                fraction[i]=trunc(other);
                other=(other-trunc(other))*10;
            }
        } 
    Decimal( const int a, const int& sizein, const int& accur):
        sgn("+"),
        int_size(sizein),
        accuracy(accur),
            number(new int[sizein]),
            fraction(new int[accur])
    {
            for(int i=0; i<int_size; i++)
            {
                number[i]=0;
            }
            for (int i=0; i<accuracy; i++)
            {
                fraction[i]=0;
            }
    }
    Decimal& operator = ( const Decimal& other)
    {
        if (number)
            delete[] number;
        number=nullptr;
        if (fraction)
            delete[] fraction;
        fraction=nullptr; 
        sgn=other.sgn;
        int_size=other.int_size;
        accuracy=other.accuracy;
        number=new int[int_size];
        fraction=new int[other.accuracy];
        for (int i=0; i<int_size; i++)
        {
            number[i]=other.number[i];
        }
        for (int i=0; i<accuracy; i++)
        {
            fraction[i]=other.fraction[i];
        } 
        return *this;
    }
    //___________________________________________________________________COMPARE______________OPERATORS__________________________________________
    bool operator == (const Decimal& other) const
    {
        if (sgn!=other.sgn)
            return false;
        for(int i=0; i<max(int_size, other.int_size); i++)
        {
            if ( (i>int_size) && (other.number[i]!=0) )
            {
                return false;
            }
            if ((i>other.int_size) && (number[i]!=0) )
            {
                return false;
            }
            if(number[i]!=other.number[i])
            {
                return false;
            }
        }
        for(int i=0; i<max(accuracy, other.accuracy); i++)
        {
            if ( (i>accuracy) && (other.number[i]!=0) )
            {
                return false;
            }
            if ((i>other.accuracy) && (number[i]!=0) )
            {
                return false;
            }
            if(number[i]!=other.number[i])
            {
                return false;
            }
        }

        return true;
    }
    friend bool operator != (const Decimal& right, const Decimal& left)
    {
        if(right==left)
        {
            return false;
        }
        else
            return true;
    }
    bool operator >= (const Decimal& other) const
    {
        if (sgn=="+" && other.sgn=="-")
        {
            return true;
        }
        if (sgn=="-" && other.sgn=="+")
        {
            return false;
        }
        if ( sgn=="+" && other.sgn=="+")
        {
            for ( int i=max(int_size, other.int_size)-1; i>=0;i--)
            {
                if ((i>int_size) && (other.number[i]!=0))
                {
                    return false;
                }
                if ((i>other.int_size) && (number[i]!=0) )
                {
                    return true;
                }
                if(number[i]>other.number[i])
                {
                    return true;
                }
                else if(number[i]<other.number[i])
                {
                    return false;
                }
            }
            for(int i=0; i<max(accuracy, other.accuracy); i++)
            {
                if ((i>accuracy) && (other.fraction[i]!=0))
                {
                    return false;
                }
                if ((i>other.accuracy) && (fraction[i]!=0) )
                {
                    return true;
                }
                if(fraction[i]>other.fraction[i])
                {
                    return true;
                }
                else if(fraction[i]<other.fraction[i])
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            for ( int i=max(int_size, other.int_size)-1; i>=0;i--)
            {
                if ((i>int_size) && (other.number[i]!=0))
                {
                    return true;
                }
                if ((i>other.int_size) && (number[i]!=0) )
                {
                    return false;
                }
                if(number[i]>other.number[i])
                {
                    return false;
                }
                else if(number[i]<other.number[i])
                {
                    return true;
                }
            }
            for(int i=0; i<max(accuracy, other.accuracy); i++)
            {
                if ((i>accuracy) && (other.fraction[i]!=0))
                {
                    return true;
                }
                if ((i>other.accuracy) && (fraction[i]!=0) )
                {
                    return false;
                }
                if(fraction[i]>other.fraction[i])
                {
                    return false;
                }
                else if(fraction[i]<other.fraction[i])
                {
                    return true;
                }
            }
            return true;
        }
    }
    friend bool operator < (const Decimal& left, const Decimal& right)
    {
        if(left>=right)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    friend bool operator <= (const Decimal& left, const Decimal& right)
    {
        if (left<right || left==right)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    friend bool operator > (const Decimal& left, const Decimal& right)
    {
        if (left<=right)
        {
            return false;
        }
        else
        {
            return true;
        }
    }
    //______________________________ARITMETIC_OPERATORS______________________________
    static Decimal Add( Decimal& right, Decimal& other) //Dictionary(int )
    {
        Decimal sum(0,max(right.int_size, other.int_size) +1, max(right.accuracy, other.accuracy));
        int b=0;
        for(int i=max(right.accuracy, other.accuracy); i >= 0; i--)
        {
            if (right.accuracy<i)
            {
                sum.fraction[i]=other.fraction[i];
                continue;
            }
            if (other.accuracy<i)
            {
                sum.fraction[i]=right.fraction[i];
                continue;
            }
            if ((right.fraction[i]+other.fraction[i]+b>9) && (i!=0))
            {
                sum.fraction[i]=right.fraction[i]+other.fraction[i]+b-10;
                //number[i-1]+=1;
                b=1;
            }
            else
            {
                sum.fraction[i]=right.fraction[i]+other.fraction[i]+b;
                b=0;
            }
        }
        int tmp=sum.fraction[0];
        sum.fraction[0]%=10;
        right.number[0]+=(tmp/10);
        b=0;
        for(int i=0; i < sum.int_size-1; i++)
        {
            if (right.int_size<i)
            {
                sum.number[i]=other.number[i];
                continue;
            }
            if (other.int_size<i)
            {
                sum.number[i]=right.number[i];
                continue;
            }
            if ((right.number[i]+other.number[i]+b>9))
            {
                sum.number[i]=right.number[i]+other.number[i]+b-10;
                //number[i-1]+=1;
                b=1;
            }
            else
            {
                sum.number[i]=right.number[i]+other.number[i]+b;
                b=0;
            }
        }
        sum.number[sum.int_size-1]=b;
        return sum;

    }
    static Decimal substract (Decimal& right,Decimal& other) //tolko a>b a>b>0
    {
        int a=0;
        //cout<<"flag1"<<endl;
        Decimal minus(0,max(right.int_size, other.int_size), max(right.accuracy, other.accuracy));
        for (int i=minus.accuracy-1; i>=0; i--)
        {
            if (i<right.accuracy && i<other.accuracy)
            {
                minus.fraction[i]=right.fraction[i]-other.fraction[i];
            
            }
            else if( i>right.accuracy)
            {
                minus.fraction[i]=-other.fraction[i];
            }
            else
            {
                minus.fraction[i]=right.fraction[i];
            }
        }
        //cout<<"flag2"<<endl;
        for (int i=minus.accuracy-1; i>0; i--)
        {
            if (minus.fraction[i]<0)
            {
                minus.fraction[i]+=10;
                minus.fraction[i-1]-=1;    
            }
        }
        if (minus.fraction[0]<0)
        {
            minus.fraction[0]+=10;
            right.number[0]-=1;   
        }
        //cout<<"flag3"<<endl;
        for (int i=0; i<minus.int_size; i++)
        {
            if (i<right.int_size && i< other.int_size)
            {
                minus.number[i]=right.number[i]-other.number[i];
            
            }
            else if( i>right.int_size)
            {
                minus.number[i]=-other.number[i];
            }
            else
            {
                minus.number[i]=right.number[i];
            }
            //cout<<"step"<<endl;
        }
        //cout<<"flag4"<<endl;
        for (int i=minus.int_size-1; i>0; i--)
        {
            if (minus.number[i]<0)
            {
                minus.number[i]+=10;
                minus.number[i-1]-=1;    
            }
        }
        //cout<<"flag5"<<endl;
        return minus;

    }
     static Decimal multipl (Decimal& right, Decimal& other)
    {
        Decimal product(0, right.int_size+other.int_size,  right.accuracy+other.accuracy);
        //int *number=new int(accuracy+other.accuracy);
        int* a=new int[right.int_size+right.accuracy];
        int right_size=right.int_size+right.accuracy;
        int* b=new int[other.int_size+other.accuracy];
        int other_size=other.int_size+other.accuracy;
        int* c=new int[product.int_size+product.accuracy];
        int product_size=product.int_size+product.accuracy;
        int k=0;
        for (int i=0; i<right.int_size; i++)
        {
            a[i]=right.number[right.int_size-1];
            //k++;
        }
        for (int i=0; i<right.accuracy; i++)
        {
            a[right.int_size+i]=right.fraction[i];
        }
         for (int i=0; i<other.int_size; i++)
        {
            b[i]=other.number[other.int_size-1];
            //k++;
        }
        for (int i=0; i<other.accuracy; i++)
        {
            b[other.int_size+i]=other.fraction[i];
        }

        for (int i=0; i<product_size; i++)
        {
            c[i]=0;
        }   
        /*cout<<"proverka"<<endl;
        for(int i=0;i<other_size; i++)
        {
            cout<<b[i];
        }
         cout<<endl<<"stop "<<endl;*/
        for (int i=other_size-1;i>=0; i-- ) //2-nd number
        {
            for(int k=right_size-1; k>=0; k--) //1-st number
            {
                c[i+k+1]+=b[i]*a[k];
            }
        }
        for (int j=product_size-1; j>0; j--)
        {
            if(c[j]>9)
            {
                int tmp=c[j];
                c[j]=c[j]%10;
                c[j-1]+=(tmp-c[j])/10;
            }
        }
        /*cout<<"proverka"<<endl;
         for(int i=0;i<product_size; i++)
        {
            cout<<c[i];
        }
        cout<<endl<<"stop "<<endl;*/
        for(int i=0;i<product.int_size; i++)
        {
            product.number[product.int_size-i-1]=c[i];
        }
        for (int i=0; i<product.accuracy; i++)
        {
            product.fraction[i]=c[product.int_size+i];
        }
        return product;
    }
    static Decimal divisa (Decimal& left, Decimal& right)
    {
        //int *number=new int(accuracy+other.accuracy);
        int* left1=new int[1+left.accuracy];
        int left1_accuracy=left.accuracy;
        int* right1=new int[1+right.accuracy];
        int right1_accuracy=right.accuracy;
        left1[0]=0;
        for (int i=0; i<left.int_size; i++)
        {
            left1[0]+=(left.number[i])*pow(10, i);
        }
        for(int i=0; i<left.accuracy; i++)
        {
            left1[1+i]=left.fraction[i];
        }
        for (int i=0; i<right.int_size; i++)
        {
            right1[0]+=right.number[i]*pow(10, i);
        }
        for(int i=0; i<right.accuracy; i++)
        {
            right1[1+i]=right.fraction[i];
        }
        //for (int i=0; i<=left1_accuracy; i++)
        //{
        //    
        //    cout<<left1[i]<<"["<<i<<"]";
        //}
        //cout<<endl;
       for (int i=1; i<=right1_accuracy; i++)
        {
            left1[0]=left1[0]*10+left1[1];
            for (int k=1; k<left1_accuracy; k++)
            {
                left1[k]=left1[k+1];
            }
            left1[left1_accuracy]=0;
            right1[0]=right1[0]*10+right1[1];
            for (int k=1; k<right1_accuracy; k++)
            {
                right1[k]=right1[k+1];
            }
            right1[right1_accuracy]=0;           
        }
        //cout<<"left number="<<left1[0]<<".";
        //for (int i=1; i<=left1_accuracy; i++)
        //{
        //    cout<<left1[i];
        //}
        //cout<<endl;
        //cout<<"right number="<<right1[0]<<endl;
        int d=right1[0];
        int *c= new int[left.accuracy+1];
        int c_accuracy=left.accuracy;
        for(int i=0; i<=c_accuracy; i++)
        {
            c[i]=0;
        }
        //c.number[0]=1;
        int k=0;
        while (k<=c_accuracy )
        {
            c[k]=left1[k]/d;
            left1[k+1]+=(left1[k]%d)*10;
            k++;
        }
        //cout<<"reverse="<<c<<endl;
        /*for (int i=0; i<=c_accuracy; i++)
        {
            cout<<c[i]<<"["<<i<<"]"<<endl;
        }*/
        cout<<endl;
        int l=size(c[0]);
        Decimal divis(0,l, c_accuracy );
        for (int i=0; i<l; i++)
        {
            divis.number[i]=c[0]%10;
            c[0]/=10;
        }
        for (int i=0; i<divis.accuracy; i++)
        {
            divis.fraction[i]=c[1+i];
        }
        //cout<<"reverse="<<c<<endl;
        return divis;
    }
    friend Decimal operator + (Decimal& a,Decimal& b)
    {
        //cout<<"a.sgn"<<a.sgn;
        //cout<<"b.sgn"<<b.sgn;

        if (a>=0 && b>=0)
        {
            //cout<<"flag1"<<endl;
            return Add(a,b);
        }
        else if(a<=0 && b<=0)
        {
            Decimal c=Add(a, b);
            c.sgn="-";
            return c;
        }
        else if(a<0 && b>0)
        {
            a.sgn="+";
            cout<<"step1"<<endl;
            if (a>b)
            {
                Decimal c=substract(a, b);
                a.sgn="-";
                c.sgn="-";
                return c;
            }
            else
            {

                Decimal c=substract(b, a);
                a.sgn="-";
                c.sgn="+";
                return c;

            }
        }
        else
        {
            b.sgn="+";
              //cout<<"step1"<<endl;
            if (a>b)
            {
                Decimal c=substract(a, b);
                b.sgn="-";
                c.sgn="+";
                return c;
            }
            else
            {

                Decimal c=substract(b, a);
                b.sgn="-";
                c.sgn="-";
                return c;

            }
        
        }
    }
    friend Decimal operator - (Decimal& a,Decimal& b)
    {
        //cout<<"a.sgn="<<a.sgn<<endl;
        //cout<<"b.sgn="<<b.sgn<<endl;
        if (b.sgn=="+")
            b.sgn="-";
        if (b.sgn=="-")
            b.sgn="+";
        
        //cout<<"b.sgn="<<b.sgn<<endl;
        Decimal c=a+b;
          //cout<<"c="<<c<<endl;
        //b.sgn="+";
        if (b.sgn=="+")
            b.sgn="-";
        if (b.sgn=="-")
            b.sgn="+";
        return c;
    }
    friend Decimal operator * (Decimal& a,Decimal& b)
    {
        //cout<<"a.sgn"<<a.sgn;
        //cout<<"b.sgn"<<b.sgn;

        if (a>=0 && b>=0)
        {
            //cout<<"flag1"<<endl;
            return multipl(a,b);
        }
        else if(a<=0 && b<=0)
        {
            Decimal c=multipl(a, b);
            return c;
        }
        else
        {
            Decimal c=multipl(a, b);
            c.sgn="-";
            return c;
        }
    }
    friend Decimal operator / (Decimal& a, Decimal& b)
    {   if (a>=0 && b>0)
        {
            //cout<<"flag1"<<endl;
            return divisa(a, b);
        }
        else if (a>=0 && b<0)
        {
            Decimal d=divisa(a, b);
            d.sgn="-";
            return d;
        }
          else if (a<=0 && b>0)
        {
            Decimal d=divisa(a, b);
            d.sgn="-";
            return d;
        }
        else
        {        
            Decimal d=divisa(a, b);
            return d;
        }
    }
     friend Decimal operator += (Decimal& a,Decimal& b)
    {
        Decimal d=a+b;
        a=d;
        return a;
    }
    friend Decimal operator -= (Decimal& a,Decimal& b)
    {
        Decimal d=a-b;
         a=d;
        return a;
    }
    friend Decimal operator *= (Decimal& a,Decimal& b)
    {
        Decimal d=a*b;
        a=d;
        return a;
    }
    friend Decimal operator /= (Decimal& a,Decimal& b)
    {
        Decimal d=a/b;
        a=d;
        return a;
    }
    //________________________INT_____________DOUBLE____________________________
    explicit operator int () 
    {
        int a;
        for (int i=int_size-1; i>=0; i--)
        {
            a+=number[i];
            a*=10;
        }
        a/=10;
        return a;
    }
    explicit operator double()
    {
        double a;
        for (int i=int_size-1; i>=0; i--)
        {
            a+=number[i];
            a*=10;
        }
        a/=10;
        int d=10;
        for (int i=0; i<accuracy; i++)
        {
            a+=((double)fraction[i])/10;
            d*=10;
        }
        return a;
    }
    //_____________________VVOD_________________VIVOD________________
    friend ostream& operator<< (ostream& out, const Decimal& a)
    {
        if ( a.sgn=="-")
        {
            out<<"-";
        }
        int b=(a.int_size)-1;
        /*if(a.number[b]!=0 && )
        {
            for (int i=b; i>=0; i--)
            {
                out<<a.number[i];
            }
        }*/
        //else
        
           for (int i=b; i>=0; i--)
            {
                out<<a.number[i];
            } 
        
        out<<".";
        for (int i=0; i<a.accuracy; i++)
        {
            out<< a.fraction[i];
        }
        //out<<endl;
        //out<<endl;
        return out;
    }
    friend istream& operator>> (istream& in,Decimal& a)
    {
        char c;
        in>>c;
        int tmp;
        int flag1=0;
        int n;
        if(c=='-')
        {
            a.sgn="-";
        }
        else
        {
            a.sgn="+";
            flag1=1;
            //tmp=c-'0';
            in.putback(c);
        }
        //int number;
        //in>>number;
        char* charnumbers=nullptr;
        int number_size=0;
        char* help=nullptr;
        char e;
        //help[1]=e;
        //in>>w;
        //if
        //number[0]=e;
        //help[0]=e;
        //in.putback(e);
        int count=0;
        while(1==1)
        {
            in>>e;
            if(e=='.')
            {
                in.putback(e);
                break;
            }
            number_size++;
            charnumbers=new char[number_size];
            for (int i=0; i<number_size-1; i++)
            {
                charnumbers[i]=help[i];
            }
            help =new char[number_size];
            charnumbers[number_size-1]=e;
            for (int i=0; i<number_size; i++)
            {
                help[i]=charnumbers[i];
            }
            count++;
        }
        a.int_size=count;
        a.number=new int[count];
        //cout<<"flag1"<<endl;
        for(int i=0; i<count; i++)
        {
            a.number[count-1-i]=charnumbers[i]-'0';
            //cout<<"rofl"<<a.number[i];
        }
        delete[] charnumbers;
        delete[] help;
        //if (count==0)
        //{
         //   charnumbers=new char[1];
        //    charnumbers[0]=e;
        //}
        /*a.int_size=n;
        a.number=new int[n];
        a.number[n]=tmp;
        for (int i=0; i<n; i++)
        {
            a.number[i]=number%10;
            number/=10;
        }
            //cout<<"flag1";
        */
        char k;
        in>>k;
        int fraction;
        in>>fraction;
        //cout<<"fraction="<<fraction<<endl;
        n=size(fraction);
        //cout<<"size_fraction is "<<n<<endl;
        a.accuracy=n;
        a.fraction=new int[n];
        //a.number[size-1]=tmp;
        for (int i=0; i<n; i++)
        {
            a.fraction[n-i-1]=fraction%10;
            fraction/=10;
        }
    return in;
    }
    ~Decimal()
    {
      delete[] fraction;
      delete[] number;
    }
};
int main()
{
    //double x=26.8;
    //double y=-26.6;
    Decimal a;
    cin>>a;
    Decimal b;
    cin>>b;
    cout<<"a="<<a<<endl;;
    cout<<"b="<<b<<endl;
    cout<<"a+b="<<a+b<<endl;
    return 0;
}
