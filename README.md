# Emergency Patrol Simulation Project
simulates a city and emergency responders (fire,police) using Dijkstra's algorithm

<h2>Objective</h2>

There is a 10*10 grid city, 4 fire trucks and 4 police vehicles. The objective is to deploy fire trucks/police vehicles 
that have the shortest distance from the location of the incident, so that the required services arrive to the scene as fast as possible.

Each road costs a different amount of time to pass, and the program's job is to put all those facts into calculation (the current location of each fire truck/police vehicle, the cost of the road on the way to the incident etc.) and deploy the emergenty patrol that takes the shortest time to arrive at the scene, and deploy it by navigating the car in the shortest path to the scene as possible.

<h2>environment</h2>
You must install Openframeworks on you computer first. After installing, you must create a github repository under 'Myapp' folder, and clone the whole project file to the git repo.

<h2>Operation Manual</h2>
After running the program, press 'l' to initialize the city. Press 's' to show the time cost of all the roads in the city.
