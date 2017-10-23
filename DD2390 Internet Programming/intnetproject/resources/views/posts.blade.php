<!-- Stored in resources/views/child.blade.php -->

@extends('layouts.master')

@section('title', 'Show all posts')

@section('sidebar')
    @parent
	<!-- Append to master sidebar -->
    <p>This is appended to the master sidebar.</p>
@endsection

@section('content')
<script>
	$(function() {
		$('div.element div.{{ $token }}-list').show();
        $('div.panel:odd').removeClass("panel-info");
        $('div.panel:odd').addClass("panel-success");
	});
</script>
    <p>
    	@if ($posts->count())
    		@foreach ($posts as $post)
            <div class="panel panel-info">
              <div class="panel-heading">{{ $post->title }}</div>
              <div class="panel-body">{{ $post->text }} </div>
            </div>	
    		@endforeach
    	@else
    		<!--{{ 'No posts found' }}-->
            <div class="embed-responsive embed-responsive-16by9">
              <iframe class="embed-responsive-item" src="https://www.youtube.com/embed/2w4l0QRL8h8"></iframe>
            </div>
    	@endif
    </p>

@endsection
