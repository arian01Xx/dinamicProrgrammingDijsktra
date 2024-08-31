#ifndef PROGRAMMING_DYNAMIC_HPP
#define PROGRAMMING_DYNAMIC_HPP

#include <vector>
#include <queue>
#include <iostream>
#include <functional>

using namespace std;

class SolutionFourtySix{
public:
	int countRestrictedPaths(int n, vector<vector<int>>& edges){
		//edges: u,v,weight
		vector<pair<int,int>> adj[n+1];

		for(auto it: edges){
			//agregar en la posición del nodo inicial el nodo de llegada y el peso
			adj[it[0]].push_back({it[1],it[2]});
			adj[it[1]].push_back({it[0],it[2]});
		}

		//DIJKSTRA's algorithm ->
		vector<int> dis(n+1,INT_MAX);
		priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
		pq.push({0,n});
		dis[n]=0;
		while(!pq.empty()){
			auto [wt,node]=pq.top();
			pq.pop();
			for(auto [v, edgeWeight]: adj[node]){
				if(dis[node]+edgeWeight < dis[v]){ //condicional del problema
					dis[v]=dis[node] + edgeWeight;
					pq.push({dis[v], v});
				}
			}
		}

		//funcion DFS con programación dinamica
		//para contar el numero de caminos restringidos desde el nodo 1 hasta el nodo n
		vector<int> dp(n+1, -1);
		function<int(int)> dfs=[&](int node)->int{
			//casos base de recursión
			if(node==1) return 1;
			if(dp[node] != -1) return dp[node];
			int ways=0;
			for(auto [v,wt]: adj[node]){
				if(dis[node] < dis[v]) ways=(ways+dfs(v))%1000000007; //para evitar desbordamientos
			}
			return dp[node]=ways;
			//la programación dinamica utiliza memoria para evitar recalculos
			//almacenados en el vector dp
		};
		return dfs(n);
	}
};

#endif