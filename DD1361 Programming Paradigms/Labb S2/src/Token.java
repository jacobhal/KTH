// De olika token-typer vi har i grammatiken
enum TokenType {
	Forw, Back, Left, Right, Up, Down, Rep, Space, Quote, Hexcolor, Int, Color, Invalid, Dot, Comma;
}

// Klass för att representera en token
// I praktiken vill man nog även spara info om vilken rad/position i
// indata som varje token kommer ifrån, för att kunna ge bättre
// felmeddelanden
class Token {
	private TokenType type;
	private Object data;
    private int line;
	
	public Token(TokenType type, int line) {
		this.type = type;
		this.data = null;
        this.line = line;
	}

	public Token(TokenType type, Object data, int line) {
		this.type = type;
		this.data = data;
        this.line = line;
	}

	public TokenType getType() { return type; }
	public Object getData() { return data; }

}
