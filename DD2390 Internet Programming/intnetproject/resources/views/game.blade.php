@extends('layouts.master')

@section('title')
Game: {{ $game->title }}
@endsection

@section('content')

   {!! Breadcrumbs::render('game', $category, $game) !!}
    <div>
      <h2 id="game-title">{{ $game->title }}</h2>
      <hr>
      <div><p style="margin: 10px 10px 10px 0;">{{ $game->description }}</p></div>
      @if(!empty($game->image) && !is_null($game->image))
        <img class="resize" src="{{ asset('images/game/' . $game->image) }}" />
      @endif
    </div>  

    <h2 id="comments-header">Comments ({{ $game->posts()->count() }})</h2>
    <hr>
    @include('includes.messages.index')
    @if(Auth::check())
        {{ Form::open(array('route' => array('post-new', $game->category->id, $game->id), 'method' => 'post', 'class' => 'new-post-form', 'value' => '{!! csrf_field() !!}')) }}
                <div class="form-group">
                  {{ Form::label('title', 'Title') }}
                  {{ Form::text('title', NULL, array('class' => 'text form-control', 'required' => 'required', 'placeholder' => 'Title', 'maxlength' => '30')) }}
                </div>
                <div class="form-inline">
                  {{ Form::label('fps', 'FPS:') }}
                  {{ Form::text('fps', NULL, array('class' => 'text form-control', 'required' => 'required', 'placeholder' => 'FPS', 'maxlength' => '10')) }}
                  {{ Form::label('quality', 'Quality:') }}
                  <select name="quality" id="quality" class="form-control">
                      <option value="Low" selected="selected">Low</option>
                      <option value="Medium">Medium</option>
                      <option value="High">High</option>
                      <option value="Ultra">Ultra</option>
                  </select>
                </div>
                <div class="form-group">
                  {{ Form::label('text', 'Text') }}
                  <textarea class="text form-control" required="required" placeholder="Text" rows="8" type="text" id="text"
                  maxlength="1000" name="textarea"></textarea>
                </div>
                  {{ Form::submit('Post comment', array('class' => 'submit btn btn-default')) }}
                  <!-- Add recover password -->
        {{ Form::close() }}
    @else
        <p style="margin: 10px 10px 10px 0;">You must log in before you can post a comment</p>
    @endif
    @if ($game->posts()->count())
        @foreach ($posts as $post)
            <div class="comment" id="{{ $post->id }}">
                <h4>{{ $post->title }}
                    <small>&nbsp&nbsp&nbsp&nbsp Author: <a href="{{ URL::route('profile', $post->author->id) }}">{{ $post->author->username }}</a>
                    &nbsp&nbsp&nbsp&nbsp Settings: { FPS: {{ $post->fps }}, Quality: {{ $post->quality }} }
                    &nbsp&nbsp&nbsp&nbsp Created at: {{ $post->created_at }}
                    </small>
                </h4>
                <hr>
                <p>{{ $post->text }}</p>
            </div>  
            @endforeach
        {{ $posts->links() }}
    @else
        <div class="alert alert-warning">
            {{ 'Be the first to comment!' }}
        </div>
    @endif

@endsection
