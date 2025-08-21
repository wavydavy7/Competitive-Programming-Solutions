#when calling inspect, retrieve the max value of max heap := otherEle
#iterate through the list of our active elephants and return the ones that are at least as big 

from collections import defaultdict
import heapq
class Q1:

    def __init__(self, elephants, schedule):
        # map of our elephants' names to their sizes
        self.sizeMap = {elephant: size for elephant,size in elephants}
        # elephants of mine that are present at any given time
        self.mine = set()

        # we have to ignore our elephants entering and leaving
        # because we flush them independently, this keeps track
        self.ignoreMap = defaultdict(int)
        
        # other elephants that are present (max heap by size)
        self.others = []
        # elephants that have left but are still in the heap (lazy deletion)
        self.othersLeft = defaultdict(int) 

        # schedule sorted by time of arrival/leaving
        self.schedule = []
        for event in schedule:
            name, arrival, departure = event
            self.schedule.append((name, arrival, "arrive"))
            self.schedule.append((name, departure, "depart"))
            self.ignoreMap[(self.sizeMap[name], arrival, "arrival")] += 1
            self.ignoreMap[(self.sizeMap[name], departure, "departure")] += 1


        self.schedule.sort(key = lambda t: t[1])
        # schedule index
        self.si = 0


    def elephantEntered(self, time, height):
        #with the time and height, can we map it to the name?
        #if someone enters, we make sure it's not our elephant: we subtract one from the ignoremap
        key = (height, time, "arrival")
        if self.ignoreMap[key] > 0:
            self.ignoreMap[key] -= 1
        else:
            heapq.heappush(self.others, -height)
    
    def elephantLeft(self, time, height):
        key = (height, time, "departure")
        if self.ignoreMap[key] > 0:
            self.ignoreMap[key] -= 1
        else:
            self.othersLeft[height] += 1 #for lazy deletion, kinda smart, that ways we don't need to use sweep line 
    
    def getBiggestElephants(self, time):
        #at a given time from s index
        while self.si < len(self.schedule) and self.schedule[self.si][1] <= time: #flush out my own elephants
            name, _, type = self.schedule[self.si]
            if type == "arrive":
                self.mine.add((name, self.sizeMap[name]))
            else:
                self.mine.remove((name, self.sizeMap[name]))
            self.si += 1
        
        while self.others:
            cur = abs(self.others[0]) #the biggest they have 
            if self.othersLeft[cur] > 0: #if it's still there, pop it from others heap 
                heapq.heappop(self.others)
                self.othersLeft[cur] -= 1
            else: #keep popping until you get to one you can stay on 
                break
        
        tallestRival = abs(self.others[0])
        candidates = [name for name,height in self.mine if height >= tallestRival]
        candidates.sort()
        return candidates