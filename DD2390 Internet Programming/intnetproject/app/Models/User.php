<?php

namespace App\Models;

use Illuminate\Foundation\Auth\User as Authenticatable;

class User extends Authenticatable
{

    protected $primaryKey = 'id';
    /**
     * The attributes that are mass assignable.
     *
     * @var array
     */
    protected $fillable = [
        'username', 'email', 'password', 'name'
    ];

    /**
     * The attributes excluded from the model's JSON form.
     *
     * @var array
     */
    protected $hidden = [
        'password', 'remember_token',
    ];

    /**
     * Get the specifiactions connected to this user.
     */
    public function specs() {
        return $this->hasOne('App\Models\Spec', 'user_id', 'id'); // If no second parameter is specified, the Spec model is assumed to have a
                                                            // user_id field (foreign key).
                                                            // Eloquent will look for the value of the user's id column in the user_id column of the Phone record.
                                                            // Third parameter specifies the local key connected to the foreign key.
    }

    /**
     * Get the posts written by this user.
     */
    public function posts() {
        return $this->hasMany('App\Models\Post', 'user_id', 'id')->orderBy('created_at', 'desc');
    }
}
