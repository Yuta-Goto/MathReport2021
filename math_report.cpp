#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define INF 2000000000
#define rep(i,n) for(int i=0;i<(n);i++)
const ll MOD = 1000000007;
typedef pair<int,int> P;

#define MAKE_NUM 2 //工程数
#define PRODUCT_NUM 2 //製品の個数

int main(){
    //変数の宣言
    int d;//何日サイクルまで許すか
    int t[MAKE_NUM];//それぞれの工程にかかる時間
    int p[PRODUCT_NUM][3];//工程１にかかる時間、工程2にかかる時間、利益

    //入力
    cin>>d;
    rep(i,MAKE_NUM) cin>>t[i];
    rep(i,PRODUCT_NUM) rep(j,3) cin>>p[i][j];

    //入力を利用して作成するDPテーブルの宣言
    vector<vector<vector<int>>> dp(PRODUCT_NUM +1,vector<vector<int>>(t[0]*d+1,vector<int>(t[1]*d+1,0)));
    vector<vector<P>> xy(t[0]*d+1,vector<P>(t[1]*d+1,P(0,0)));

    //動的計画法
    for(int i=0;i<PRODUCT_NUM;i++){
        for(int j=0;j<=t[0]*d;j++){
            for(int k=0;k<=t[1]*d;k++){
                if(j-p[i][0]<0 || k-p[i][1]<0){
                    dp[i+1][j][k]=dp[i][j][k];//製品X(またはY)を作らない
                }else{
                    dp[i+1][j][k]=max(dp[i][j][k],dp[i+1][j-p[i][0]][k-p[i][1]]+p[i][2]);//製品X(またはY)を作る
                    if(dp[i+1][j][k]!=dp[i][j][k]){
                        int a=0,b=0;//製品Xについてのループを回しているときにはa=1、Yについてのループを回しているときにはb=1。
                        if(i==0) a=1,b=0;//このif文によって、実際に使った製品のみをカウントできる
                        else a=0,b=1;
                        xy[j][k].first=xy[j-p[i][0]][k-p[i][1]].first+a;
                        xy[j][k].second=xy[j-p[i][0]][k-p[i][1]].second+b;
                    }
                }
            }
        }
    }

    //宣言
    vector<pair<float,float>> ans;//総利益の最大値とかかる日数
    vector<pair<int,int>> num;//i+1日間で利益の最大値を得ようとしたときに作るXとYの個数
    //それぞれのvector配列に、動的計画法によって得た解を入力
    for(float i=1.0;i<d+0.5;i+=1.0){
        ans.push_back(P((float)dp[2][t[0]*i][t[1]*i]/i,i));
        num.push_back(xy[t[0]*(int)i][t[1]*(int)i]);
    }

    //ansをソート。総利益の最大値に着目して、降順にソートする。
    sort(ans.begin(),ans.end(),greater<P>());
    //上記のソートにより、総利益の最大値が同じ場合、日数が多い方が配列の先頭に来ている。日数に関しては最小化したいので、以下のwhile処理を行う。
    int now=0;
    while(ans[now].first==ans[now+1].first) now++;
    //最小化された、必要な日数をint型変数dateに代入。
    int date=ans[now].second;
    
    //「純利益の最大値、必要な日数の最小値、その日数で作る製品X,Yの数」を出力
    cout<<ans[now].first<<" "<<date<<" "<<num[date-1].first<<" "<<num[date-1].second<<endl;
    return 0;
}