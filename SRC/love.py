import pygame
import math

class graph:
    def __init__(self):
        pygame.font.init()
        self.mydisplay = 0
        self.screen = 0
        self.color = (0,0,0)
        self.linewidth = 1
        self.scroll = [0,0]
        self.font = pygame.font.SysFont("comicsans",20)

    def update(self):
        self.scroll = [0,0]
        pygame.display.flip()

    def newImage(self,path):
        return pygame.image.load(path).convert_alpha()

    def newFont(self,type,size):
        return pygame.font.SysFont(type,size),

    def display(self,size,caption):
        self.mydisplay = pygame.display.set_mode((size),pygame.RESIZABLE )#pygame.FULLSCREEN )
        self.screen = self.mydisplay
        pygame.display.set_caption(caption)

    def draw(self,image,x,y,r,sx,sy):
        mm = pygame.transform.flip(image,sx < 0,sy < 0)
        mm = pygame.transform.scale(mm,(int(sx),int(sy)))
        mm = rotate3(mm,-r)
        self.screen.blit(mm[0],(x- mm[1] + self.scroll[0],y - mm[2] + self.scroll[1]))

    def draw2(self,image,x,y):
        self.screen.blit(image,(x + self.scroll[0],y + self.scroll[1]))

    def print(self,text,x,y):
        tt =  self.font.render(text,1,self.color)
        self.screen.blit(tt,(x + self.scroll[0],y + self.scroll[1]))

    def setFont(self,font):
        self.font = font

    def getFontSize(self,text):
        return self.font.size(text)

    def clear(self,r,g,b,a=255):
        self.screen.fill((r,g,b,a))

    def setColor(self,r,g,b,a =255):
        self.color = (r,g,b,a)

    def setLineWidth(self,width):
        self.linewidth = width

    def rectangle(self,mode,x,y,width,height):
        if mode == 'fill':
            m = 0
        elif mode == 'line':
            m = self.linewidth
        pygame.draw.rect(self.screen,self.color,(x + self.scroll[0],y + self.scroll[1],width,height),m)

    def circle(self,mode,x,y,radius):
        if mode == 'fill':
            m = 0
        elif mode == 'line':
            m = self.linewidth
        pygame.draw.circle(self.screen,self.color,(int(x + self.scroll[0]),int(y + self.scroll[1])),int(radius),m)

    def ellipse(self,mode,x,y,width,height):
        if mode == 'fill':
            m = 0
        elif mode == 'line':
            m = self.linewidth
        pygame.draw.ellipse(self.screen,self.color,(x + self.scroll[0] - width,y + self.scroll[1] - height,width*2,height*2),m)
     
    def polygon(self,mode,*points):
        x = []
        y = []
        for i,point in enumerate(points):
            if i % 2 == 0:
                x.append(math.floor(point + self.scroll[0]))
            else:
                y.append(math.floor(point + self.scroll[1]))
        '''for point in points:
            for i,p in enumerate(point):
                p +=  self.scroll[i]'''
        if mode == 'fill':
            m = 0
        elif mode == 'line':
            m = self.linewidth
        pygame.draw.polygon(self.screen,self.color,list(zip(x,y)),m)

    def polygon2(self,mode,*points):
        pointcopy = []
        for point in points:
            pointcopy.append([point[0] + self.scroll[0],point[1] + self.scroll[1]])
        if mode == 'fill':
            m = 0
        elif mode == 'line':
            m = self.linewidth
        pygame.draw.polygon(self.screen,self.color,pointcopy,m)

    def line(self,*points):
        x = []
        y = []
        for i,point in enumerate(points):
            if i % 2 == 0:
                x.append(point + self.scroll[0])
            else:
                y.append(point + self.scroll[1])
        pygame.draw.lines(self.screen,self.color,False,list(zip(x,y)),self.linewidth)

    def translate(self,x=0,y=0):
        self.scroll[0] = x
        self.scroll[1] = y

    def newCanvas(self,width,height):
        return pygame.Surface((width,height),pygame.SRCALPHA).convert_alpha()

    def setCanvas(self,name = False):
        if not name :
            self.screen = self.mydisplay
        else:
            name.fill(0)
            self.screen = name
    def getSize(self,image):
        return image.get_size()

    def getWidth(self,image):
        return image.get_width()

    def scale(self,image,sx,sy):
        return pygame.transform.scale(image,(sx,sy))

graphics = graph()

class keys:
    def __init__(self):
        self.key = 0

    def update(self):
        self.key = pygame.key.get_pressed()

    def isDown(self,k):
        return self.key[eval('pygame.K_'+k)]

keyboard = keys()

class M:
    def __init__(self):
        self.x = 0
        self.y = 0
        self.width = 1
        self.height = 1
        self.continues = [False,False,False]
        self.conn = [False,False,False]

    def update(self,camX =0,camY =0):
        self.x = pygame.mouse.get_pos()[0] - camX
        self.y = pygame.mouse.get_pos()[1] - camY

    def isDown(self,button,debounce = False):
        if debounce:
            for i in range(3):
                self.conn[i] = False
            if pygame.mouse.get_pressed()[button - 1]:
                self.conn[button - 1] = self.continues[button - 1]
                self.continues[button - 1] = False
            else:
                self.continues[button - 1] = True
            return self.conn[button - 1]
        else:
            return pygame.mouse.get_pressed()[button - 1]

mouse = M()

''' dd = pygame.surfarray.pixels3d(love.graphics.screen)
    for x in range(1,50):
        dd[x + love.mouse.x][love.mouse.y:50+ love.mouse.y] += x
    del dd'''

def collides(obj1, obj2):
    if obj1.y <= obj2.y + obj2.height and obj1.y + obj1.height >= obj2.y and obj1.x <= obj2.x + obj2.width and obj1.x + obj1.width >= obj2.x:
        if abs(obj1.y - obj2.y) >= abs(obj1.x - obj2.x):
            if obj1.y <= obj2.y:
                return 'up'
            if obj1.y > obj2.y:
                return 'down'

        if abs(obj1.y - obj2.y) <= abs(obj1.x - obj2.x):
            if obj1.x <= obj2.x:
                return 'right'
            if obj1.x > obj2.x:
                return 'left'

def getangle(x1,y1,x2,y2):
    if math.atan2((y2 - y1),(x2 - x1)) >= 0:
      return math.atan2((y2 - y1),(x2 - x1))
    else:
      return math.atan2((y2 - y1),(x2 - x1)) + 2*math.pi

def rotate(vec,theta):
    return [vec.x*math.cos(theta) - vec.y*math.sin(theta),vec.y*math.cos(theta) + vec.x*math.sin(theta)]


def rotate2(image,angle):
    w1,h1 = image.get_size()
    mm = pygame.transform.rotozoom(image,math.degrees(angle),1)
    w,h = mm.get_size()
    th = getangle(0,0,(w1/2),(h1/2))
    r = math.sqrt((w1/2)**2+(h1/2)**2)
    return [mm,w/2 - r*math.cos(th - angle),h/2 - r*math.sin(th - angle)]

def rotate3(image,angle):
    w1,h1 = image.get_size()
    mm = pygame.transform.rotate(image,math.degrees(angle))
    w,h = mm.get_size()
    th = getangle(0,0,(w1/2),(h1/2))
    r = math.sqrt((w1/2)**2+(h1/2)**2)
    return [mm,w/2 - r*math.cos(th - angle),h/2 - r*math.sin(th - angle)]

def Lengthening(x1,y1,x2,y2,u_d,r_l):
    x = x2 + u_d * (x2 - x1)/ math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    y = y2 + u_d * (y2 - y1)/ math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    m = x + r_l * (y - y1)/ math.sqrt((y1 - y)**2 + (x - x1)**2)
    n = y + r_l * (x1 - x)/ math.sqrt((y1 - y)**2 + (x - x1)**2)
    return [m,n]

   


