@extends('layouts.master')

@section('title')
View profile: {{ $user->username }}
@endsection

@section('content')
    <div id="profile-wrapper">
        <h2>Specifications for user: {{ $user->username }}</h2>
        <hr>
        @if(!is_null($specs))
            <p><strong>CPU:</strong>                {{ !empty($specs->cpu) ? $specs->cpu : 'Not set' }}</p>
            <p><strong>GPU:</strong>                {{ !empty($specs->cpu) ? $specs->gpu : 'Not set' }}</p>
            <p><strong>Power supply:</strong>       {{ !empty($specs->cpu) ? $specs->power : 'Not set' }}</p>
            <p><strong>Motherboard:</strong>        {{ !empty($specs->cpu) ? $specs->motherboard : 'Not set' }}</p>
            <p><strong>Computer case:</strong>      {{ !empty($specs->cpu) ? $specs->computercase : 'Not set' }}</p>
            <p><strong>RAM:</strong>                {{ !empty($specs->cpu) ? $specs->ram : 'Not set' }}</p>
            <p><strong>Harddrive 1:</strong>        {{ !empty($specs->cpu) ? $specs->hd1 : 'Not set' }}</p>
            <p><strong>Harddrive 2:</strong>        {{ !empty($specs->cpu) ? $specs->hd2 : 'Not set' }}</p>
            <p><strong>Operating System:</strong>   {{ !empty($specs->cpu) ? $specs->os : 'Not set' }}</p>
        @else
            <p>This user has not added his/her specs yet.</p>
        @endif
        <h2 style="margin: 10px 10px 10px 0;">Comments by this user</h2>
        <hr>
        @if ($user->posts()->count())
            @foreach ($user->posts as $post)
                <div class="comment" id="{{ $post->id }}">
                    <h4><a href="{{ URL::route('game', array($post->game->category->token, $post->game->token, '#' . $post->id)) }}">{{ $post->title }}</a>
                        <small>&nbsp&nbsp&nbsp&nbsp Author: <a href="{{ URL::route('profile', $post->author->id) }}">{{ $post->author->username }}</a>
                        &nbsp&nbsp&nbsp&nbsp Settings: { FPS: {{ $post->fps }}, Quality: {{ $post->quality }} }
                        &nbsp&nbsp&nbsp&nbsp Created at: {{ $post->created_at }}
                        </small>
                    </h4>
                    <p style="margin: 10px 10px 10px 0;">Game: {{ $post->game->title }}</p>
                    <hr>
                    <p>{{ $post->text }}</p>
                </div>  
            @endforeach
        @endif
    </div>

@endsection
