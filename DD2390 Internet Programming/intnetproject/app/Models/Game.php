<?php

namespace App\Models;

use Illuminate\Database\Eloquent\Model;

class Game extends Model
{
    /**
	 * The database table used by the model.
	 *
	 * @var string
	 */
	protected $table = 'games';

	/**
	 * The mass assignable fields for pm.
	 * 
	 * @var array(string)
	 */
	protected $fillable = array('title', 'description', 'category_id');

	/**
	 * Get the Category associated with this game
	 */
	public function category() {
		return $this->belongsTo('App\Models\Category');
	}

	/**
	 * Get the posts associated with this game
	 */
	public function posts() {
		return $this->hasMany('App\Models\Post')->orderBy('created_at', 'desc');
	}

	
}
