// Ett syntaxträd
abstract class ParseTree {
	abstract public String process();
}

// Ett syntaxträd som representerar en "leaf(...)"
class Int extends ParseTree {
	Integer data;
	public Int(Integer data) {
		this.data = data;
	}
	public String process() {
		return data.toString();
	}
}

// Ett syntaxträd som representerar en "leaf(...)"
class Position extends ParseTree {
    Object data;
    TokenType token;
    double [] position;
    int angle;
    boolean pen;
    String color;
    public Position(TokenType token, Object data, double[] position, int angle, String color) {
        this.data = data;
        this.token = token;
        this.position = position;
        this.angle = angle;
        this.color = color;
    }
    public double[] calcValues(){
        switch(token) {
            case Forw: position[0] = position[0] + (Integer) data*Math.cos(Math.PI*angle/180);
                       position[1] = position[1] + (Integer) data*Math.cos(Math.PI*angle/180);
            case Back: position[0] = position[0] - (Integer) data*Math.cos(Math.PI*angle/180);
                       position[1] = position[1] - (Integer) data*Math.cos(Math.PI*angle/180);
            case Left: angle = angle + (Integer) data;
            case Right: angle = angle - (Integer) data;
            case Up: pen = false;
            case Down: pen = true;
            case Color: color = (String) data;
        }
        return position;
    }
    public String process() {
        return data.toString();
    }
}

// Ett syntaxträd som representerar en "branch(... , ...)"
class BranchNode extends ParseTree {
	ParseTree left, right;
	public BranchNode(ParseTree left, ParseTree right) {
		this.left = left;
		this.right = right;
	}
	public String process() {
		return "[" + right.process() + ";" + left.process() + "]";
	}
}