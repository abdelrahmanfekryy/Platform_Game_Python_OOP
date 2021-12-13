gameWidth, gameHeight =   1280, 720
renderorder = []
coinno = 0
npcno = 0
from myengine import updateShape

def computeX(item):
        item.box.dy = 0
        item.box.dx = 0
        updateShape(item.box)
        item.xmin = item.box.pnt[0].loc
        item.xmax = item.box.pnt[0].loc
        for x in range(1,item.box.no):
            if item.box.pnt[x].loc.x < item.xmin.x:
                item.xmin = item.box.pnt[x].loc
            if item.box.pnt[x].loc.x > item.xmax.x:
                item.xmax = item.box.pnt[x].loc

def prioritycheck(item1,item2):
        if item2.xmax.x >= item1.xmin.x and item2.xmin.x <= item1.xmax.x:
            if ((item2.xmin.y - item1.xmin.y < ((item1.xmin.y - item1.xmax.y)/(item1.xmin.x - item1.xmax.x))*(item2.xmin.x -  item1.xmin.x)) and (item2.xmax.y -  item1.xmin.y < ((item1.xmin.y - item1.xmax.y)/(item1.xmin.x - item1.xmax.x))*(item2.xmax.x -  item1.xmin.x))) or ((item1.xmin.y - item2.xmin.y > ((item2.xmin.y - item2.xmax.y)/(item2.xmin.x - item2.xmax.x))*(item1.xmin.x -  item2.xmin.x)) and (item1.xmax.y -  item2.xmin.y > ((item2.xmin.y - item2.xmax.y)/(item2.xmin.x - item2.xmax.x))*(item1.xmax.x -  item2.xmin.x))):
                item2.downlist.append(item1)

            if ((item1.xmin.y - item2.xmin.y < ((item2.xmin.y - item2.xmax.y)/(item2.xmin.x - item2.xmax.x))*(item1.xmin.x -  item2.xmin.x)) and (item1.xmax.y -  item2.xmin.y < ((item2.xmin.y - item2.xmax.y)/(item2.xmin.x - item2.xmax.x))*(item1.xmax.x -  item2.xmin.x))) or ((item2.xmin.y - item1.xmin.y > ((item1.xmin.y - item1.xmax.y)/(item1.xmin.x - item1.xmax.x))*(item2.xmin.x -  item1.xmin.x)) and (item2.xmax.y -  item1.xmin.y > ((item1.xmin.y - item1.xmax.y)/(item1.xmin.x - item1.xmax.x))*(item2.xmax.x -  item1.xmin.x))):
                item1.downlist.append(item2)

def priorityclear(item):
    item.downlist = []

def iterate(item):
    for el in item.downlist:
        for el2 in el.downlist:
            if el2 not in item.downlist:
                item.downlist.append(el2)
    item.priority = len(item.downlist)

def normalizeangle(angle):
    return (angle + 360) % 360