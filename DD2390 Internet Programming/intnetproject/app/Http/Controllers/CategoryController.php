<?php

namespace App\Http\Controllers;

use Auth, Input, Redirect, View, Log, Hash, Response, Request;
//use Illuminate\Http\Request;
use App\Models\User;
use App\Models\Post;
use App\Models\Category;
use App\Models\Spec;
use App\Models\Game;
use Validator;
use App\Http\Controllers\Controller;

class CategoryController extends Controller {
    /**
     * Get a category by token and send that to a view. With the help of relationships
     * defined in the models, it is easy to get all the games from the category in the view.
     */
    public function getGames($token) {
        try {
            $category = Category::where('token', '=', $token)->firstOrFail();
        } catch (ModelNotFoundException $e){
            Log::error('No category found!'); // This should never happen
        }
        $games = $category->games;
        $view = View::make('games')
            ->with('category', $category)
            ->with('games', $games);
        return $view;
    }  
    /**
     * Get a specific game by its token.
     */
    public function getGame($categorytoken, $token) {
        try {
            $category = Category::where('token', '=', $categorytoken)->first();
            $game = Game::where('token', '=', $token)
                ->where('category_id', '=', $category->id)
                ->first();
            if(is_null($game)) {
                abort(404);
            }
        } catch (ModelNotFoundException $e){
            Log::error('No game found!'); // This should never happen unless someone types the adress
            abort(404);
        }
        $posts = $game->posts()->paginate(10)->fragment('comments-header');
        $view = View::make('game')
            ->with('game', $game)
            ->with('posts', $posts)
            ->with('category', $category);
        return $view;
    }    

    /**
     * Ajax search games
     */
    public function getSearch($categorytoken = '') {
        if(isset($categorytoken) && !empty($categorytoken) && !is_null($categorytoken)) {
            $searchword = Input::get('searchword');
            /*
            if(Request::ajax()) {

                else {
                $games = Game::where('title', 'like', $searchword)
                        ->where('category_id', '=', $category->id)
                        ->get();
                $view = View::make('games')
                    ->with('category', $category)
                    ->with('games', $games);
                return $view;
            }*/
            $category = Category::where('token', '=', $categorytoken)->first();
                

            $games = Game::where('title', 'LIKE', '%'.$searchword.'%')
                ->where('category_id', '=', $category->id)
                ->orderBy('title', 'asc')
                ->get()
                ->toJson();
           
            echo $games;
            //echo $games;
        } else {
            $searchword = Input::get('searchword');
            $games = Game::where('title', 'LIKE', '%'.$searchword.'%')
                ->orderBy('title', 'asc')
                ->get()
                ->toJson();
            echo $games;
        }
           
    }
}