<?php

/*
|--------------------------------------------------------------------------
| Routes File
|--------------------------------------------------------------------------
|
| Here is where you will register all of the routes in an application.
| It's a breeze. Simply tell Laravel the URIs it should respond to
| and give it the controller to call when that URI is requested.
|
*/





/*
Route::get('auth/login', 'Auth\AuthController@getLogin');
Route::get('auth/logout', 'Auth\AuthController@getLogout');

// Registration routes...
Route::get('auth/register', 'Auth\AuthController@getRegister');
Route::post('auth/register', 'Auth\AuthController@postRegister');
*/





/*
|--------------------------------------------------------------------------
| Application Routes
|--------------------------------------------------------------------------
|
| This route group applies the "web" middleware group to every route
| it contains. The "web" middleware group is defined in your HTTP
| kernel and includes session state, CSRF protection, and more.
|
*/

/**
 * ALL ROUTES THAT USES SESSIONS MUST PASS THROUGH THIS MIDDLEWARE GROUP.
 */
Route::group(['middleware' =>[ 'web']], function () {

	/**
	 * General routes
	 */
	
	Route::get('/', ['as' => 'index', function()
	{
		return view('index');
	}]);

	/**
	 * About and contact routes
	 */
	Route::get('/about',	['as' => 'about', function() {
		return view('website.about');
	}]);
	Route::get('/contact',	['as' => 'contact', function() {
		return view('website.contact');
	}]);
   
   	/**
   	 * Authentication routes
   	 */
	Route::post('/login', 	[ 	'as' => 'login', 'uses' => 'GuestController@postSignIn']);
	Route::get('/logout', 	[   'as' => 'logout', 'uses' => 'GuestController@getLogout']);

	/**
	 * Register routes
	 */
	Route::get('/register', 		[   'as' => 'register-new', 'uses' => 'GuestController@getRegister']);
	Route::post('/register/done', 	[	'as' => 'register-done', 'uses' => 'GuestController@postRegister']);

	/**
	 * Ajaxsearch for games
	 */
	Route::get('/search/games/{categorytoken?}', 	[   'as' => 'ajax-games-search', 'uses' => 'CategoryController@getSearch']);

	/**
	 * Post routes
	 */
	Route::post('/new/post/{category}/{id}', [	'as' => 'post-new', 'uses' => 'PostController@addPost']);

	/**
	 * Game routes
	 */
	/**
	 * Get all games for a specific category
	 */
	Route::get('/games/{category}', 	[   'as' => 'games', 'uses' => 'CategoryController@getGames']);

	/**
	 * Get a specific game by token
	 */
	Route::get('/games/{categorytoken}/{token}', 	[   'as' => 'game', 'uses' => 'CategoryController@getGame']);

	/**
	 * Redirect to profile page for given user id
	 */
	Route::get('/user/profile/{id}', 	[   'as' => 'profile', 'uses' => 'UserController@getProfile']);

	/**
	 * Private user routes
	 */
	Route::get('/user/settings', 	[   'as' => 'settings', 'uses' => 'UserController@getSettings']);
	Route::post('/user/settings/update', 	[   'as' => 'settings-update', 'uses' => 'UserController@postSettings']);


	/*
	 * Get all posts
	 
	Route::get('/game/{token}', 	[   'as' => 'posts', 'uses' => 'PostController@getPosts']);
	*/
});
