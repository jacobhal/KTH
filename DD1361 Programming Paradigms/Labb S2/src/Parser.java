import java.lang.reflect.Array;

/**
 * En rekursiv medåknings-parser för binära träd
 */


public class Parser {
	private Lexer lexer;
    private int [] position = new int[2];

	public Parser(Lexer lexer) {
		this.lexer = lexer;
	}

	public ParseTree parse() throws SyntaxError {
		// Startsymbol är Action()
		ParseTree result = Action();
		// Borde inte finnas något kvar av indata när vi parsat ett bintree
		if (lexer.hasMoreTokens())
			throw new SyntaxError();
		return result;
	}

	private ParseTree Action() throws SyntaxError {
		// Kika på nästa indata-token för att välja produktionsregel
		Token t = lexer.peekToken();
        // kom ihåg vilken operation vi utför
        TokenType type = t.getType();
        // Parsedel för olika riktningar
		if (type == TokenType.Forw|type == TokenType.Back|type == TokenType.Right|type == TokenType.Left) {
            // regeln BinTree -> Leaf(Number) ska användas
            lexer.nextToken(); // ät upp t
            // sedan borde det vara ett eller flera space
            if (lexer.peekToken().getType() != TokenType.Space) throw new SyntaxError();
            // nästa token borde vara en Int
            Token param = lexer.nextToken();
            if (param.getType() != TokenType.Int) throw new SyntaxError();
            // sedan valfria space samt punkt
            lexer.nextToken();
            if (lexer.peekToken().getType() == TokenType.Space && lexer.nextToken().getType() == TokenType.Dot | lexer.peekToken().getType() != TokenType.Dot){
        } else{
                throw new SyntaxError();
            }
			// returnera parseträd som bara består av en löv-nod med
			// rätt data
			return new Position(type, (Integer)param.getData(), position);
            // Parsedel för Rep
		} else if (t.getType() == TokenType.Rep) {
			// regeln BinTree -> Branch(BinTree,BinTree) ska användas
			// ät upp t
			lexer.nextToken();
			// sedan borde det vara en vänsterparentes
			if (lexer.nextToken().getType() != TokenType.Space) throw new SyntaxError();
			// sedan borde det vara en Int
            if (lexer.nextToken().getType() != TokenType.Int) throw new SyntaxError();
            // föjt av mer space..
            if (lexer.nextToken().getType() != TokenType.Space) throw new SyntaxError();
            // sedan borde quotetecken följt av actions komma
            if (lexer.nextToken().getType() != TokenType.Quote) throw new SyntaxError();
			ParseTree left = Action();
			// sedan ett komma
			if (lexer.nextToken().getType() != TokenType.Comma) throw new SyntaxError();
			// sedan ett till bintree
			ParseTree right = BinTree();
			// sedan en högerparentes
			if (lexer.nextToken().getType() != TokenType.RParen) throw new SyntaxError();
			return new BranchNode(left, right);
		} else {
			throw new SyntaxError();
		}	
	}
}

