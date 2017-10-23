<?php

namespace App\Providers;

use Illuminate\Support\ServiceProvider;

use App\Models\Post;
use App\Models\Game;
use View, DB;

class AppServiceProvider extends ServiceProvider
{
    /**
     * Bootstrap any application services.
     *
     * @return void
     */
    public function boot()
    {
        $latestposts = Post::orderBy('created_at', 'desc')->take(5)->get();
        View::share('latestposts', $latestposts);
        $allgames = Game::orderBy('title', 'asc')->get();
        View::share('allgames', $allgames);
    }

    /**
     * Register any application services.
     *
     * @return void
     */
    public function register()
    {
        //
    }
}
