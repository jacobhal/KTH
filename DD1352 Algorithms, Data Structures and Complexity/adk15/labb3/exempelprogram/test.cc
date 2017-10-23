/**
 * Exempel på in- och utdatahantering för maxflödeslabben i kursen
 * ADK.
 *
 * Använder iostreams i C++.
 * Anmärkning: scanf/printf-rutinerna från C-exemplet går att använda
 * även i C++ och är ofta märkbart snabbare än cin/cout som det här
 * programmet använder.
 *
 * Author: Per Austrin
 */

#include <iostream>
#include <map>
#include <vector>

using std::cin;
using std::cout;
using std::cerr;


struct Edge {
  Edge(int x, int y, int a): v1(x), v2(y), c(a){}
  int v1;
  int v2;
  int c;
};

int gX, gY, nrOfEdges;
//std::multimap<int, int> edges;

std::vector<Edge> edges;

/**
 * Helper functions
 */

/*
  Add new edge to Vector edges with values v1, v2 and capacity/flow c.
 */
void newEdge(int v1, int v2, int c = 0) {
  edges.push_back(Edge(v1,v2,c));
}

void readBipartiteGraph() {
  int x, y, e; // x och y är antalet hörn i grafen x respektive y och e är antalet kanter.
  // Om x = 3 och y = 2 kommer de se ut som följer: x = {1,2,3}, y = {4,5}
  // Läs antal hörn och kanter

  cin >> x >> y >> e;
  gX = x;
  gY = y;
  nrOfEdges = e;

  // Läs in kanterna, dessa läses in som 2 heltal, t.ex. 1 5 innebär att det finns en kant från 1 till 5.
  for (int i = 0; i < e; ++i) {
    int a, b;
    cin >> a >> b;
    newEdge(a, b);
    //edges.insert(std::pair<int, int>(a, b)); // TODO: Ska man ta med inversen?
  }
}

/*
  Responsible for
 */
void writeFlowGraph() {

  // debugutskrift
  cerr << "Börjar skriva ut flödesgraf (icke-löst)." << std::endl;
  /*
    gX = Antal hörn i graf X.
    gY = Antal hörn i graf Y.
    v = Totala antalet hörn i vår flödesgraf (utan källa och sänka).
    s = Källa (Börjar alltid på 0).
    t = Sänka (Antal hörn + 1).
    e = Antal kanter.
   */
  int v = gX+gY, e = nrOfEdges, source = 0, target = v+1;

  // Källa och sänka ska tydligen vara värden som finns i grafen, inte 0 och antal hörn + 1?
  source = 1;
  target = v;

 

  // Skriv ut antal hörn och kanter samt källa och sänka
  cout << v << "\n" << source << " " << target << "\n" << e << "\n"; 


  /*for (int i = 0; i <= e; ++i) {
    //int u, v, c;
    for(int j = 0; j < edges.count(i); ++j) {
      cout << i << " " << edges[i] << " " << 1 << "\n";
    }
    // Kant från u till v med kapacitet c
    //cout << u << " " << v << " " << c << "\n";
  }*/

/*
  for (auto it = edges.begin(); it != edges.end(); ++it) {
      cout << (*it).first << " " << (*it).second << " " << 1 << std::endl;
  }
  */

  for(int i = 0; i < edges.size(); ++i) {
      cout << edges[i].v1 << " " << edges[i].v2 << " " << edges[i].c << std::endl;
  }

   // Skapa kanter mellan Källa och gX samt gY och Sänka.
  // TODO: Inverser eller ej?
  for(int i = 0; i < gX; ++i) {
    if(i <= gX) {
      newEdge(source, i, 1);
      //edges.insert(std::pair<int, int>(source, i));
    } else {
      newEdge(i, target, 1);
    }
  }
  // Var noggrann med att flusha utdata när flödesgrafen skrivits ut!
  // Flush makes sure that the buffer is cleared and the characters are written to their destination
  cout.flush();

  // Debugutskrift
  cerr << "Skickade iväg flödesgrafen\n";
}

/*
  Responsible for reading a maxflow solution from stdin and converting it to a solution 
  for the maximum matching problem.
 */

void readMaxFlowSolution() {
  // debugutskrift
  cerr << "Börjar läsa Maxflödeslösning." << std::endl;
  int vertices, e, source, target, flow;

  // Läs in antal hörn, källa, sänka, flöde och antal kanter.
  // (Antal hörn, källa och sänka borde vara samma som vi i grafen vi
  // skickade iväg)
  cin >> vertices >> source >> target >> flow >> e;
  // debugutskrift
  // cout << vertices << "\n" << source << " " << target << " " << flow << "\n" << edges << "\n";

  // Clear edges vector.
  edges.clear();

  for (int i = 0; i < e; ++i) {
    int u, v, edgeFlow;
    // Flöde f från u till v
    cin >> u >> v >> edgeFlow;
    newEdge(u, v, edgeFlow);
    // debugutskrift
    //cout << u << " " << v << " " << edgeFlow;
  }

  cout << gX << " " << gY << "\n" << e << std::endl;
  for (int i = 0; i < e; ++i) {
    cout << edges[i].v1 << " " << edges[i].v2 << "\n";
  }
  


  // TODO: Översätt till matchningslösning
}

/*
  Responsible for writing the final maximum matching problem for a bipartite graph.
 */
void writeBipMatchSolution() {
  int x = 17, y = 4711, maxMatch = 0;

  // Skriv ut antal hörn och storleken på matchningen
  cout << x << " " << y << "\n" << maxMatch << "\n";

  for (int i = 0; i < maxMatch; ++i) {
    int a, b;
    // Kant mellan a och b ingår i vår matchningslösning
    cout << a << " " << b << "\n";
  }

}


int main(void) {
  // Två trick för att göra cin/cout lite snabbare.
  // Se http://kattis.csc.kth.se/doc/iostreamio
  std::ios::sync_with_stdio(false);
  cin.tie(0);

  

  // TODO: Väldigt osäker om multimap är bästa datastrukturen, en array skulle förmodligen funka lika bra eller bättre
  //std::multimap<int, int> edges; // Lagrar alla kanter i den bipartita grafen.
  readBipartiteGraph(); // Läser in bipartit graf

  writeFlowGraph(); // 

  readMaxFlowSolution();

  //writeBipMatchSolution();

  // debugutskrift
  cerr << "Bipred avslutar\n";
  return 0;
}

/*


Du ska i tre steg skriva ett program som får en bipartit graf som indata och producerar en matchning av maximal storlek som utdata genom att reducera (transformera) matchningsproblemet till flödesproblemet. Korrekthet och effektivitet testas genom att lösningarna på de tre stegen skickas till Kattis. För att klara labben ska du bli godkänd av Kattis på de tre stegen samt redovisa labben för en handledare. Kattis kontrollerar både att programmet gör rätt och att det löser problemet tillräckligt snabbt. Kattis klarar av programspråken Java, C, C++ och Python, men tidskraven i denna labb gör att vi avråder från Python.
Steg 1: 
Reducera problemet till flödesproblemet
Du ska skriva ett program som löser matchningsproblemet med hjälp av en svart låda som löser flödesproblemet. Programmet ska fungera enligt denna översiktliga programstruktur:
Läs indata för matchningsproblemet från standard input.
Översätt matchningsinstansen till en flödesinstans.
Skriv indata för flödesproblemet till standard output (se till att utdata flushas).
Den svarta lådan löser flödesproblemet.
Läs utdata för flödesproblemet från standard input.
Översätt lösningen på flödesproblemet till en lösning på matchningsproblemet.
Skriv utdata för matchningsproblemet till standard output.
Se nedan hur in- och utdataformaten för matchnings- och flödesproblemen ser ut.
Ditt program ska lösa problemet effektivt. Kattis kommer att provköra programmet på bipartita grafer på upp till (5000+5000) hörn och upp till 10000 kanter. Kattis känner till problemet som oldkattis:adkreducetoflow. Det finns ett programskelett för steg 1 i några olika språk på katalogen /info/adk15/labb3/exempelprogram

Steg 2: 
Lös flödesproblemet
Nu ska du skriva ett program som löser flödesproblemet. Programmet ska läsa indata från standard input och skriva lösningen till standard output. Se nedan hur in- och utdataformaten för flödesproblemet ser ut.
Ditt program ska lösa problemet effektivt. Kattis kommer att provköra programmet på generella flödesgrafer på upp till 2000 hörn och 10000 kanter. Kattis känner till problemet som oldkattis:adkmaxflow.

Steg 3: 
Kombinera steg 1 & 2
I steg 1 löste du matchningsproblemet med hjälp av en lösning till flödesproblemet. I steg 2 löste du flödesproblemet. Nu ska du kombinera dessa lösningar till ett enda program genom att byta ut kommunikationen av flödesinstansen över standard input och standard output till ett funktionsanrop. Programmet ska fortfarande läsa indata från standard input och skriva lösningen till standard output.
Ditt program ska lösa problemet effektivt. Kattis kommer att provköra programmet på bipartita grafer på upp till (5000+5000) hörn och upp till 10000 kanter. Kattis känner till problemet som oldkattis:adkbipmatch.


===Matchningproblemet===
Givet en bipartit graf G = (X,Y,E) finn en maximal matchning.

Indata
Den första raden består av två heltal som anger antalet hörn i X respektive Y.
Den andra raden består av ett tal som anger |E|, det vill säga antalet kanter i grafen.
De följande |E| raderna består var och en av två heltal som svarar mot en kant.
Hörnen numreras från 1 och uppåt. Om man angett a hörn i X och b hörn i Y så låter vi X = {1, 2,..., a} och Y = {a+1, a+2,..., a+b}. En kant anges med ändpunkterna (först X-hörnet och sedan Y-hörnet).
Exempel: En graf kan till exempel kodas så här.
2 3
4
1 3
1 4
2 3
2 5
Denna graf har alltså X = {1, 2} och Y = {3, 4, 5}. Kantmängden E innehåller kanterna (1, 3), (1, 4), (2, 3) och (2, 5).

Utdata
Först skrivs en rad som är densamma som den första i indata, och därefter en rad med ett heltal som anger antalet kanter i den funna matchningen. Därefter skrivs en rad för varje kant som ingår i matchningen. Kanten beskrivs av ett talpar på samma sätt som i indata.
Exempel: Om vi har grafen ovan som indata så kan utdata se ut så här.
2 3
2
1 3
2 5


===Flödesproblemet===
Givet en flödesgraf G = (V,E) finn ett maximalt flöde. Lös flödesproblemet med Edmonds-Karps algoritm, det vill säga Ford-Fulkersons algoritm där den kortaste stigen hittas med breddenförstsökning.
Ford-Fulkersons algoritm i pseudokod
c[u,v] är kapaciteten från u till v, f[u,v] är flödet, cf[u,v] är restkapaciteten.
for varje kant (u,v) i grafen do 
    f[u,v]:=0; f[v,u]:=0 
    cf[u,v]:=c[u,v]; cf[v,u]:=c[v,u] 
while det finns en stig p från s till t i restflödesgrafen do 
    r:=min(cf[u,v]: (u,v) ingår i p) 
    for varje kant (u,v) i p do 
         f[u,v]:=f[u,v]+r; f[v,u]:= -f[u,v] 
         cf[u,v]:=c[u,v] - f[u,v]; cf[v,u]:=c[v,u] - f[v,u]
Indata
Den första raden består av ett heltal som anger antalet hörn i V.
Den andra raden består av två heltal s och t som anger vilka hörn som är källa respektive utlopp.
Den tredje raden består av ett tal som anger |E|, det vill säga antalet kanter i grafen.
De följande |E| raderna består var och en av tre heltal som svarar mot en kant.
Hörnen numreras från 1 och uppåt. Om man angett a hörn i V så låter vi V = {1, 2,..., a}. En kant anges med ändpunkterna (först från-hörnet och sedan till-hörnet) följt av dess kapacitet.
Exempel: En graf kan till exempel kodas så här.
4
1 4
5
1 2 1
1 3 2
2 4 2
3 2 2
3 4 1

Utdata
Den första raden består av ett heltal som anger antalet hörn i V.
Den andra raden består av tre heltal s,t, samt flödet från s till t.
Den tredje raden består av ett heltal som anger antalet kanter med positivt flöde.
Därefter skrivs en rad för varje sådan kant. Kanten beskrivs av tre tal på liknande sätt som i indata, men i stället för kapacitet har vi nu flöde.
Exempel: Om vi har grafen ovan som indata så kan utdata se ut så här.
4
1 4 3
5
1 2 1
1 3 2
2 4 2
3 2 1
3 4 1

===Testning===
I katalogen /info/adk15/labb3 ligger programmen bipgen, flowgen, maxflow, combine och matchtest som du kan köra för att testa dina program.
Programmet bipgen genererar en slumpvis vald bipartit graf. Grafen skrivs på standard output på ovan angivet format för indata till matchningsprogrammet. 

/info/adk15/labb3/bipgen x y e 

ger en graf med x hörn i X, y hörn i Y och e kanter.
Programmet flowgen genererar en slumpvis vald flödesgraf. Grafen skrivs på standard output på ovan angivet format för indata till flödesprogrammet. 

/info/adk15/labb3/flowgen v e c 

ger en graf med v hörn och e kanter vars kapaciteter är positiva heltal inte större än c.
Programmet maxflow löser flödesproblemet och kan användas som svart låda i steg 1. maxflow tar en flödesgraf på standard input och skriver ut ett maximalt flöde på standard output.
Programmet combine är ett hjälpprogram som du kan använda dig av i steg 1 för att få ditt program att prata med den svarta lådan. 

/info/adk15/labb3/combine java MatchReduce \; /info/adk15/labb3/maxflow < graffil > matchfil 

kommer att köra java MatchReduce som lösning på steg 1, och använda kursens maxflow-program som svart låda. Indatagrafen tas från filen graffil och utdata skickas till filen matchfil.
Programmet matchtest läser en graf följt av utdata från ett matchningsprogram (alltså, först grafen och sedan matchningen) och kontrollerar att matchningen är maximalt stor. Utdata skrivs på standard outputoch kan vara Matchning av maximal storlek, Matchning av mindre än maximal storlek eller Ingen matchning.
Så här kan du använda bipgen och matchtest för att testa din lösning på steg 3 (minlabb).
/info/adk15/labb3/bipgen 5000 5000 10000 > graffil 
minlabb < graffil > matchfil 
cat graffil matchfil | /info/adk15/labb3/matchtest
Bra testfall att testa de tre stegen med finns på /info/adk15/labb3/testfall/
Om du inte vet vad tecknen >, < och | betyder i exemplen ovan så kan du titta i Unixhäftet eller fråga en labbhandledare. För att kolla hur lång tid ditt program kör på dina egna testfall kan du använda kommandot time och titta på user time.

 */
