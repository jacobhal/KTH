<?php

namespace App\Http\Controllers;

use Auth, Input, Redirect, View, Log, Hash;
use Illuminate\Http\Request;
use App\Models\User;
use App\Models\Spec;
use Validator;
use App\Http\Controllers\Controller;
use Illuminate\Foundation\Auth\ThrottlesLogins;
use Illuminate\Foundation\Auth\AuthenticatesAndRegistersUsers;

class GuestController extends Controller {

    /**
     * Handles user sign in post request. Logs user in 
     * if possible, or redirects with error message.
     *
     * @return Response
     */
    public function postSignIn() { 
        if (Auth::attempt(['username' => Input::get('username'), 'password' => Input::get('password'), 'active' => 1])) {
            Log::info('LOGGED IN');
            return Redirect::route('index')
                ->with('success', 'You have been logged in.');
        }
        Log::error('LOGIN FAILED');
        // Return and display error messages
        return Redirect::back()
            ->withInput()
            ->with('error', 'Wrong username or password.');
    }

    /**
     * Logout a user
     */
    public function getLogout() {
        Auth::logout();
        return Redirect::route('index')
                ->with('success', 'You have been logged out.');
    }

    /**
     * Register
     */
    public function getRegister() {
        return View::make('auth.register');
    }

    /**
     * Perform an actual registration
     */
    public function postRegister(Request $request) {
        $this->validate($request, [
        'username'                  => 'required|between:5,30|unique:users',
        'email'                     => 'required|between:5,30', 
        'password'                  => 'required|between:5,30',
        'password_confirmation'     => 'required|between:5,30',
        ]);

        $data = Input::all();
        // Add user to database 
        $user = new User();
        $user->username = $data['username'];
        $user->email = $data['email'];
        $user->password = Hash::make($data['password']); 
        $user->privileges = 'user';
        $user->save();

        $specs = new Spec();
        $specs->user_id = $user->id;
        $specs->save();

        // TODO: redirect back
        return Redirect::route('index')
                ->with('success', 'Your account has now been created. You can now log in.');
    }
}