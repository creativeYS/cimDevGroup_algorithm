// 백준 1446번:지름길

#include <iostream>
#include <vector>


struct Graph
{
	int start;
	int end;
	int weight;
};

struct Graph graph_input(int s, int e, int w)
{
	struct Graph arr;
	arr.start = s;
	arr.end = e;
	arr.weight = w;
	return arr;
}

int main()
{
	int N = 0;
	int D = 0;
	int s = 0, e = 0, w = 0;
	std::vector <struct Graph> *arr;
	int* dist;

	std::cin >> N >> D;
	dist = new int[D + 1];
	arr = new std::vector<Graph>[D + 1];
	
	for (int i = 0; i < N; i++)
	{
		std::cin >> s >> e >> w;
		arr[s].push_back(graph_input(s,e,w));
	}
	for (int i = 0; i <= D; i++)
		dist[i] = i;


	for (int i = 0; i <= D; i++)
	{
		if (i != 0)
		{
			dist[i] = (dist[i] < dist[i - 1] + 1) ? dist[i] : dist[i - 1] + 1;  // 지름길 거리와 직접 거리를 비교
		}
		for (Graph road : arr[i])
		{
			if (road.end <= D && dist[road.end] > road.weight + dist[i])  // 끝점이 목적지(D) 이내에 있고, 기존에 기록된 거리와 대소관계 비교.
				dist[road.end] = road.weight + dist[i];
		}
	}
	std::cout << dist[D] << std::endl;
	delete[] dist;
	delete[] arr;

	return 0;
}
