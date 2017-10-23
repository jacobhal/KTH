import java.util.*;

public class Algorithms {

	/*
	 * Helper functions
	 */



	/*
	 * Algorithms
	 */

	// Minimax implementation
	public int miniMax(GameState gameState, Player player, Vector<GameState> nextStates) {
		int bestPossible;
		// Terminal state
	    if(nextStates.size() == 0) { 
	    	if(gameState.isXWin()) {
	    		return 1;
	    	} else if(gameState.isOWin()) {
	    		return -1;
	    	} else {
	    		return 0;
	    	}
	    } else { // GO DEEPER
	         
	        if(true) { // Player A
	        	bestPossible = Integer.MIN_VALUE;
	        	for(int i = 0; i < nextStates.size(); i++) {

	        	}

	        } else { // Player B
	        	bestPossible = Integer.MAX_VALUE;
	        	for(int i = 0; i < nextStates.size(); i++) {
	        		
	        	}

	        }

	        return bestPossible;


        }
    }
}