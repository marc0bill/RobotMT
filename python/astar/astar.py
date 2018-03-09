from math import sqrt, pi
import random as random
import numpy as np


class AStarNode:
	def __init__(self,ix0,iy0,delta_x,delta_y,DistanceObstacle=1e9):
		self.G = 1e9 	# G, distance parcourue
		self.H = 1e9 	# H, distance a vol d'oiseau
		self.F = 1e9	# F, poids du noeud
		self.Ang = 0.0	# Angle du robot sur ce point
		self.TpsTrajet = 1e9
		self.DistanceObstacle = DistanceObstacle
		self.ix = ix0
		self.iy = iy0
		self.delta_x = delta_x
		self.delta_y = delta_y
		self.x = ix0*delta_x
		self.y = iy0*delta_y
		self.Parent = None
		self.ListO_next = None
		self.parcourus = False
		self.delta=(self.delta_x+self.delta_y)/4.0
	def setObstacle(self, NewDist):
		self.DistanceObstacle = NewDist
	def addObstacle(self,x_obs,y_obs):
		NewDist = sqrt((self.x-x_obs)**2+(self.y-y_obs)**2)
		if NewDist < self.DistanceObstacle:
			self.DistanceObstacle = NewDist
	
	def setDistanceObstacle(self,Dist):
		self.DistanceObstacle = Dist
	
	def clean(self):
		self.G = 1e9
		self.H = 1e9
		self.F = 1e9
		self.Parent = None
		self.ListO_next = None
		self.parcourus = False
	
	def printNode(self):
		print("G:",self.G)
		print("H:",self.H)
		print("F:",self.F)
		print("parcourus:",self.parcourus)
		print(self.ListO_next)
	
	def moveCost(self, current, fin,distance,Ang_new,DistObsMin,DistObsMax,VtsMax,VtsAng):
	 #	Vts=VtsMax/2.0
		if(self.DistanceObstacle<=DistObsMin):
			Vts=1e-9
		else :
			if(self.DistanceObstacle>=DistObsMax):
				Vts=VtsMax
			else:
				Vts=VtsMax*(self.DistanceObstacle-DistObsMin)/(DistObsMax-DistObsMin)+1e-9
		
		
		
		H_new = (sqrt((self.x-fin.x)**2+(self.y-fin.y)**2)+ random.uniform(-self.delta, self.delta))/Vts

		TpsTrajet_new=distance/Vts+abs(Ang_new-current.Ang)/VtsAng
		G_new = current.G + TpsTrajet_new
		
		F_new = G_new + H_new
		if self.F > F_new:
			self.H = H_new
			self.G = G_new
			self.F = F_new
			self.Ang = Ang_new
			self.TpsTrajet=TpsTrajet_new
			return True 	#Renvoie True si mise a jours des valeurs
		else:
			return False	#Renvoie False si aucune valeurs mise a jours
		
	def addListO(self,NewNode):
		#if (NewNode.F < self.F + random.uniform(-self.delta, self.delta)):
		#if (NewNode.F < self.F):
		if (NewNode.F < self.F):
			NewNode.ListO_next = self
			return NewNode
		else :
			if (NewNode.F > self.F):
				if self.ListO_next == None :
					self.ListO_next=NewNode
				else:
					self.ListO_next=self.ListO_next.addListO(NewNode)
				return self
			else:
				if random.sample([True,False],1)[0]:
					NewNode.ListO_next = self
					return NewNode

	def delListO(self,Node):
		if self == Node:
			return self.ListO_next
		else:
			self.ListO_next = self.ListO_next.delListO(Node)
			return self
	
	def getListO(self):
		print(self.ix,self.iy,self.F,self.G,self.H)
		if self.ListO_next == None :
			return
		else:
			self.ListO_next.getListO()
			
	def printParcours(self):
		print(self.ix,self.iy,self.F,self.H,self.G,self.parcourus,self.ListO_next)
		if self.Parent == None :
			return
		else:
			self.Parent.printParcours()
		
	def getParcours(self,X,Y,Ang,TpsTrajet,Obs):
		X.insert(0,self.x)
		Y.insert(0,self.y)
		Ang.insert(0,self.Ang)
		TpsTrajet.insert(0,self.TpsTrajet)
		Obs.insert(0,self.DistanceObstacle)
		if self.Parent == None :
			return
		else:
			self.Parent.getParcours(X,Y,Ang,TpsTrajet,Obs)
		
class Pathfinder:
	def __init__(self , x_max=2000.0 , y_max=3000.0 , nb_x=200 , nb_y=300 , DistanceObstacleMin=200.0, DistanceObstacleMax=2000.0):
		self.graph=[]
		self.delta_x=x_max/nb_x
		self.delta_y=y_max/nb_y
		self.delta_xy=sqrt(self.delta_y*self.delta_y + self.delta_x*self.delta_x)
		self.TableDist=[[self.delta_xy , self.delta_y , self.delta_xy],[self.delta_x , 0.0 , self.delta_x],[self.delta_xy , self.delta_y , self.delta_xy]]
		self.TableAng=[[5.0*pi/4.0 , -pi/2.0 , -pi/4.0],[pi , 0.0 , 0.0],[3.0*pi/4.0 , pi/2.0 , pi/4.0]]
		self.x_max=x_max
		self.y_max=y_max
		self.nb_x=nb_x
		self.nb_y=nb_y
		
		self.DistanceObstacleMin = DistanceObstacleMin
		self.DistanceObstacleMax = DistanceObstacleMax
		
		self.X=np.linspace(0,self.x_max,self.nb_x)
		self.Y=np.linspace(0,self.y_max,self.nb_y)
		
		
#		self.VtsMax = VtsMax
		
		self.iObsMax_y = int(DistanceObstacleMax/self.delta_y)
		self.iObsMax_x = int(DistanceObstacleMax/self.delta_x)
		for iy in range(self.nb_y):
			self.graph.insert(iy,[])
			for ix in range(self.nb_x):
				node=AStarNode(ix,iy,self.delta_x,self.delta_y,DistanceObstacleMax)
				self.graph[iy].insert(ix,node)
		
		
	def pathfinding(self,x_start,y_start,ang_start,x_fin,y_fin,VtsMax=1000.0,VtsAng=10.0):
		ix_start = int (x_start/self.delta_x)
		iy_start = int (y_start/self.delta_y)
		ix_fin = int (x_fin/self.delta_x)
		iy_fin = int (y_fin/self.delta_y)
		
		NodeStart=self.graph[iy_start][ix_start]
		NodeFin=self.graph[iy_fin][ix_fin]
		
		NodeStart.G=0.0
		NodeStart.moveCost(NodeStart, NodeFin,0.0,ang_start,self.DistanceObstacleMin,self.DistanceObstacleMax,VtsMax,VtsAng)
		HeadListO=NodeStart
		NodeCurrent=HeadListO
		while (NodeCurrent.ix != ix_fin) | (NodeCurrent.iy != iy_fin):
			NodeCurrent.parcourus=True
			for i,j in [[-1,-1],[-1,0],[-1,1],[0,-1],[0,1],[1,-1],[1,0],[1,1]]:
				ix=i+NodeCurrent.ix
				iy=j+NodeCurrent.iy
				if (0<=ix<self.nb_x) & (0<=iy<self.nb_y):
					if (self.graph[iy][ix].DistanceObstacle>self.DistanceObstacleMin) & (self.graph[iy][ix].parcourus == False):
						if self.graph[iy][ix].moveCost(NodeCurrent,NodeFin,self.TableDist[j+1][i+1],self.TableAng[j+1][i+1],self.DistanceObstacleMin,self.DistanceObstacleMax,VtsMax,VtsAng):
							if self.graph[iy][ix].Parent != None:
								HeadListO=HeadListO.delListO(self.graph[iy][ix]); 
							HeadListO=HeadListO.addListO(self.graph[iy][ix])
							self.graph[iy][ix].Parent=NodeCurrent
			HeadListO=HeadListO.delListO(NodeCurrent); 
			NodeCurrent=HeadListO
			if NodeCurrent == None:
				break
		return NodeCurrent
	
	def clean(self):
		for iy in range(self.nb_y):
			for ix in range(self.nb_x):
				self.graph[iy][ix].clean()
	def dellObstacle(self):
		for iy in range(self.nb_y):
			for ix in range(self.nb_x):
				self.graph[iy][ix].setDistanceObstacle(self.DistanceObstacleMax)
	def addObstacle(self,x_obs,y_obs):
		ix_obs = int (x_obs/self.delta_x)
		iy_obs = int (y_obs/self.delta_y)
		for j in range(-self.iObsMax_y,self.iObsMax_y):
			for i in range(-self.iObsMax_x,self.iObsMax_x):
				iy=iy_obs+j
				ix=ix_obs+i
				if (0<=ix<self.nb_x) & (0<=iy<self.nb_y):
					self.graph[iy][ix].addObstacle(x_obs,y_obs)
	def setObstacle(self,ObsMap):
		for iy in range(self.nb_y):
			for ix in range(self.nb_x):
				self.graph[iy][ix].setObstacle(ObsMap[ix,iy])
				
	def getTable(self):
		#X=[]
		#Y=[]
		
		Obs=np.zeros((self.nb_x,self.nb_y))
		
		for iy in range(self.nb_y):
			for ix in range(self.nb_x):
		#		X.insert(0,self.graph[iy][ix].x)
		#		Y.insert(0,self.graph[iy][ix].y)
				Obs[ix][iy]=self.graph[iy][ix].DistanceObstacle
		return Obs
				
class AStar(object):
	def __init__(self, graph):
		self.graph = graph
	def heuristic(self, node, start, end):
		raise NotImplementedError
	def search(self, start, end):
		openset = set()
		closedset = set()
		current = start
		openset.add(current)
		while openset:
			current = min(openset, key=lambda o:o.g + o.h)
			if current == end:
				path = []
				while current.parent:
					path.append(current)
					current = current.parent
				path.append(current)
				return path[::-1]
			openset.remove(current)
			closedset.add(current)
			for node in self.graph[current]:
				if node in closedset:
					continue
				if node in openset:
					new_g = current.g + current.move_cost(node)
					if node.g > new_g:
						node.g = new_g
						node.parent = current
					else:
						node.g = current.g + current.move_cost(node)
						node.h = self.heuristic(node, start, end)
						node.parent = current
						openset.add(node)
		return None
 
# class AStarNode(object):
	# def __init__(self):
		# self.g = 0
		# self.h = 0
		# self.parent = None
	# def move_cost(self, other):
		# raise NotImplementedError
 
# class AStarGrid(AStar):
	# def heuristic(self, node, start, end):
		# return sqrt((end.x - node.x)**2 + (end.y - node.y)**2)
 
# class AStarGridNode(AStarNode):
	# def __init__(self, x, y):
		# self.x, self.y = x, y
		# super(AStarGridNode, self).__init__()

	# def move_cost(self, other):
		# diagonal = abs(self.x - other.x) == 1 and abs(self.y - other.y) == 1
		# return 14 if diagonal else 10