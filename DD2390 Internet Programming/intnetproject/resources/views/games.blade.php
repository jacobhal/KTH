@extends('layouts.master')

@section('title')
    Genre: {{ $category->name }}
@endsection

@section('scripts')
    {{ Html::script('js/ajaxsearch.js') }}
@endsection

@section('content')
<?php 
    $counter = array();
    foreach($games as $game) {
        $nrofcomments = $game->posts()->count();
        $counter[$game->id] = $nrofcomments;
    }
?>
        <script>
            $(function() {
                $('#basic-addon1').click( function(event) {
                    event.preventDefault();
                }); 
            });
        </script>
        {!! Breadcrumbs::render('games', $category) !!}
        <h2>Pick a game</h2>
        <hr>
        @if ($category->games()->count())
        <div class="col-lg-7 searchbar">
            <div class="input-group">
                <a href="{{ URL::route('ajax-games-search', $category->token) }}" class="input-group-addon" id="basic-addon1">
                    <span class="glyphicon glyphicon-search" aria-hidden="true"></span>
                </a>
                <a href="{{ Request::url() }}" hidden="true" id="hiddendummy">Test</a>
                <form id="search-games" onkeyup="$.searchQ({{ json_encode($counter) }});" method="post">
                    <input type="text" class="form-control" placeholder="Search..." aria-describedby="basic-addon1" 
                  id="searchbar" autofocus="autofocus" style="border-top-right-radius: 5px;border-bottom-right-radius: 5px;">
                </form>
            </div>
        </div>
        <div class="col-lg-12" id="gameslist">
            @foreach ($games as $game)
            <div class="col-lg-7" style="border: 2px solid #ccc; margin: 5px 0; padding: 10px; border-radius: 5px;">
                <a href="{{ URL::route('game', array($category->token, $game->token)) }}" role="button">
                    {{ $game->title }}
                </a>
                <span style="float: right; min-width: 40px; margin: 0; padding: 0;">
                    <span class="glyphicon glyphicon-comment" aria-hidden="true" style="margin: 0; padding; 0;"></span>
                    <span style="margin: 0; padding; 0;float: right;">
                    {{ $game->posts()->count() }}
                    </span>
                </span>     
            </div>  
            @endforeach
        </div>
        @else
            <div class="alert alert-warning">
                {{ 'There are currently no games in this genre' }}
            </div>
        @endif

@endsection
