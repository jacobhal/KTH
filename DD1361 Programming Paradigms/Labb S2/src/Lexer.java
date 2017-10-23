import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.Reader;
import java.util.ArrayList;
import java.util.List;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * En klass för att göra lexikal analys, konvertera indataströmmen
 * till en sekvens av tokens.  Den här klassen läser in hela
 * indatasträngen och konverterar den på en gång i konstruktorn.  Man
 * kan tänka sig en variant som läser indataströmmen allt eftersom
 * tokens efterfrågas av parsern, men det blir lite mer komplicerat.
 */
public class Lexer {
	private List<Token> tokens;
	private int currentToken;

	// Hjälpmetod som läser in innehållet i en inputstream till en
	// sträng
	private static String readInput(InputStream f) throws java.io.IOException {
		Reader stdin = new InputStreamReader(f);
		StringBuilder buf = new StringBuilder();
		char input[] = new char[1024];
		int read = 0;
		while ((read = stdin.read(input)) != -1) {
			buf.append(input, 0, read);
		}
		return buf.toString();
	}


	public Lexer(InputStream in) throws java.io.IOException {
		String input = Lexer.readInput(in);
        input = input.toUpperCase();
        input = input.replaceAll("%.*", "");
        //System.out.print(input);
		// Ett regex som beskriver hur ett token kan se ut, plus whitespace (som vi här vill ignorera helt)
        //String regex = "(FORW|BACK|LEFT|RIGHT)\\s+\\d+\\s*\\.|UP\\s*\\.|DOWN\\s*\\.|^COLOR #([0-9A-Fa-f]){6}$|REP\\s+\\d+\\s+\".+\"\\s*\\.";
		Pattern tokenPattern = Pattern.compile("FORW|BACK|RIGHT|LEFT|COLOR|REP|DOWN|UP|\\.|\\s+|\"|#|[0-9]+|,|%");
        Pattern linePattern = Pattern.compile("\\n");
        Matcher line = linePattern.matcher(input);
		Matcher m = tokenPattern.matcher(input);
		int inputPos = 0;
        int lineCount = 1;
		tokens = new ArrayList<Token>();
		currentToken = 0;
		// Hitta förekomster av tokens/whitespace i indata
		while (m.find()) {

            if(line.find()) lineCount++;
            if(m.group().matches("%")) ;
			// Om matchningen inte börjar där den borde har vi hoppat
			// över något skräp i indata, markera detta som ett
			// "Invalid"-token
			if (m.start() != inputPos) {
				tokens.add(new Token(TokenType.Invalid, lineCount));
			}
           // if(System.lineSeparator().equals(m.group().charAt(inputPos))) {
            //    lineCount++;
            //}
			// Kolla vad det var som matchade
			if (m.group().equals("FORW"))
				tokens.add(new Token(TokenType.Forw, lineCount));
			else if (m.group().equals("BACK"))
				tokens.add(new Token(TokenType.Back, lineCount));
			else if (m.group().equals("LEFT"))
				tokens.add(new Token(TokenType.Left, lineCount));
			else if (m.group().equals("RIGHT"))
				tokens.add(new Token(TokenType.Right, lineCount));
			else if (m.group().equals("UP"))
				tokens.add(new Token(TokenType.Up, lineCount));
            else if (m.group().equals("DOWN"))
                tokens.add(new Token(TokenType.Down, lineCount));
            else if (m.group().equals("COLOR"))
                tokens.add(new Token(TokenType.Color, lineCount));
            else if (m.group().matches("\\s+"))
                tokens.add(new Token(TokenType.Space, lineCount));
            else if (Character.isDigit(m.group().charAt(0)))
                tokens.add(new Token(TokenType.Int, Integer.parseInt(m.group()), lineCount));
            else if (m.group().matches("\""))
                tokens.add(new Token(TokenType.Quote, lineCount));
            else if (m.group().matches("#([0-9A-Fa-f]){6}"))
                tokens.add(new Token(TokenType.Hexcolor, m.group(), lineCount));
            else if (m.group().equals("REP"))
                tokens.add(new Token(TokenType.Rep, lineCount));
            else if (m.group().matches("\\."))
                tokens.add(new Token(TokenType.Dot, lineCount));
            else if (m.group().matches(","))
                tokens.add(new Token(TokenType.Comma, lineCount));
            inputPos = m.end();
		}
		// Kolla om det fanns något kvar av indata som inte var ett token
		if (inputPos != input.length()) {
			tokens.add(new Token(TokenType.Invalid, lineCount));
		}
		// Debug-kod för att skriva ut token-sekvensen
		for (Token token: tokens)
		   System.out.println(token.getType());
        System.out.println(lineCount);;
    }

	// Kika på nästa token i indata, utan att gå vidare
	public Token peekToken() throws SyntaxError {
		// Slut på indataströmmen
		if (!hasMoreTokens()) 
			throw new SyntaxError();
		return tokens.get(currentToken);
	}

	// Hämta nästa token i indata och gå framåt i indata
	public Token nextToken() throws SyntaxError {
		Token res = peekToken();
		++currentToken;
		return res;
	}

	public boolean hasMoreTokens() {
		return currentToken < tokens.size();
	}
}