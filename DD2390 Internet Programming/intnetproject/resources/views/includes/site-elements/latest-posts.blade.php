<div id="latest-posts">
	<h3 id="latest-posts-header">Latest Posts</h3>
	@if (!empty($latestposts))   
	    @foreach ($latestposts as $post)
	   	 <div class="latest-posts-element">
	   	 	<p style="font-size: 13px;"><a href="{{ URL::route('game', array($post->game->category->token, $post->game->token, '#' . $post->id)) }}">{{ $post->title }}</a></p>
	   	 	<p>Author: <a href="{{ URL::route('profile', $post->author->id) }}">{{ $post->author->username }}</a></p>
	   	 	<p>Game: {{ $post->game->title }}</p>
	   	 	<p>Created at: {{ $post->created_at }}</p>
	   	 	<p>Settings: { FPS: {{ $post->fps }}, Quality: {{ $post->quality }} }</p>
	   	 </div>
	    @endforeach
	@endif
</div>