<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Post extends Model
{
    /**
	 * The database table used by the model.
	 *
	 * @var string
	 */
	protected $table = 'posts';

	/**
	 * The mass assignable fields for a post.
	 * 
	 * @var array(string)
	 */
	protected $fillable = array('category_id', 'text', 'title');

	/**
	 * Get the Category associated with this post
	 */
	public function category() {
		return $this->belongsTo('App\Models\Category', 'category_id');
	}

	/**
	 * Get the user who wrote this post
	 */
	public function author() {
		return $this->belongsTo('App\Models\User', 'user_id');
	}

	/**
	 * Get the game related to this post
	 */
	public function game() {
		return $this->belongsTo('App\Models\Game', 'game_id');
	}

	
}
