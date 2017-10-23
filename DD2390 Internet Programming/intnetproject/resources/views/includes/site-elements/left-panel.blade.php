<div id="left-panel">
	<h3 id="left-panel-header">Game Genres</h3>
	<div class="element {{ Request::is('games/action') ? 'active' : '' }} {{ Request::is('games/action/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'action') }}">Action</a>
	</div>
	<div class="element {{ Request::is('games/action-adventure') ? 'active' : '' }} 
	{{ Request::is('games/action-adventure/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'action-adventure') }}">Action-adventure</a>
	</div>
	<div class="element {{ Request::is('games/adventure') ? 'active' : '' }} 
	{{ Request::is('games/adventure/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'adventure') }}">Adventure</a>
	</div>
	<div class="element {{ Request::is('games/mmo') ? 'active' : '' }} 
	{{ Request::is('games/mmo/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'mmo') }}">MMO</a>
	</div>
	<div class="element {{ Request::is('games/rpg') ? 'active' : '' }} 
	{{ Request::is('games/rpg/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'rpg') }}">RPG</a>
	</div>
	<div class="element {{ Request::is('games/simulation') ? 'active' : '' }} 
	{{ Request::is('games/simulation/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'simulation') }}">Simulation</a>
	</div>
	<div class="element {{ Request::is('games/strategy') ? 'active' : '' }} 
	{{ Request::is('games/strategy/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'strategy') }}">Strategy</a>
	</div>
	<div class="element {{ Request::is('games/sport') ? 'active' : '' }} 
	{{ Request::is('games/sport/' . '*') ? 'active' : '' }}">
		<a href="{{ URL::route('games', 'sport') }}">Sport</a>
	</div>
	
</div>