import React, { useEffect } from 'react';
import { useNavigate, Outlet } from 'react-router-dom';
import './components.css/AuthUser.css';
import ProtectedRoutes from './ProtectedRoutes';
import Login from "./Login";

function AuthUser() {

	const navigate = useNavigate();

	const useAuth = () => {
		const user = { LoggedIn: false };
		return user && user.LoggedIn;
	};
	
	const ProtectedRoutes = () => {
		const isAuth = useAuth();
		return isAuth ? <Outlet /> : <Login />
	};
	
	 useEffect(() => {
		let paramters = new URLSearchParams(window.location.search);
		let codeParam = paramters.get('code');
		if (codeParam){
			const apiUrl = 'http://localhost:9080/login';
			const dto = {
				key1: 'token',
				key2: codeParam,
			};

			fetch(apiUrl, {
				method: 'POST',
				header: {
					'Content-Type': 'application/json',
				},
				body: JSON.stringify(dto),
			})
			.then(response => {
				if (!response.ok) {
					throw new Error('Network response was not ok');
				  }
				return response.json(); // Parse the JSON response
				})
				.then(data => {
				  // Handle the API response data
				  console.log(data);
				 <ProtectedRoutes /> 
				  navigate('/main', { data });
				 
				})
				.catch(error => {
				  // Handle any errors
				  console.error('Error sending POST request:', error);
				});
		};
	}, []);


	return (
		<div className='loader-container'>
			<div class="loader" >
			</div>
		</div>
	);
	
}

export default AuthUser;