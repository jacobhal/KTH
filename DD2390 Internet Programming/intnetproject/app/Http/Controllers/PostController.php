<?php

namespace App\Http\Controllers;

use Auth, Input, Redirect, View, Log, Hash, Response;
use Illuminate\Http\Request;
//use Illuminate\Http\Request;
use App\Models\User;
use App\Models\Post;
use App\Models\Category;
use Validator;
use App\Http\Controllers\Controller;
use Illuminate\Foundation\Auth\ThrottlesLogins;
use Illuminate\Foundation\Auth\AuthenticatesAndRegistersUsers;

class PostController extends Controller {
    public function getPosts($token) {
        try {
            $category = Category::where('name', '=', $token)->firstOrFail();
        } catch (ModelNotFoundException $e){
            Log::error('No category found!'); // This should never happen
        }
        $posts = $category->posts;
        $view = View::make('posts')
                ->with('posts', $posts)
                ->with('token', $token);
        // Uncomment getposts script in master in order to use ajax
        if(Request::ajax()) {
            return $view->renderSections()['content'];
        }
        //return Response::json( $posts );
        return $view;
    }  
    /**
     * Add a new post
     */
    public function addPost($category, $id, Request $request) {

        $error = array();
        $validator = Validator::make(Input::all(),
        [
            'title'                  => 'required',
            'fps'                    => 'required|numeric', 
            'quality'                => 'required',
            'textarea'                   => 'required'
        ]);

        if ($validator->fails() || !empty($error)) {
            $messages = $validator->messages();

            return Redirect::back()
            ->with('error', array_merge($messages->all(), $error))
            ->withInput();
        }

        $data = Input::all();
        // Add user to database 
        $post = new Post();
        $post->title = $data['title'];
        $post->fps = $data['fps'];
        $post->quality = $data['quality']; 
        $post->text = $data['textarea'];
        $post->category_id = $category;
        $post->game_id = $id;
        $post->user_id = Auth::user()->id;
        $post->save();

        return Redirect::back()->with('success', 'Your comment has been submitted.');
    } 
}